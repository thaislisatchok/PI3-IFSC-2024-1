#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_client.h"
#include "ping/ping_sock.h"
#include "lwip/inet.h"

#define WIFI_SSID "SEU_SSID"
#define WIFI_PASS "SUA_SENHA"
#define SERVER_URL "http://seu-servidor.com/receber_dados"
#define pings 5 // Para checar latência

static const char *TAG = "[MAIN] Wi-Fi Analyzer";
static const char *target_SSID = WIFI_SSID;
static char post_data[1024];  // Buffer para armazenar os dados a serem enviados


uint32_t latency[pings];
uint32_t ping_count = 0;

static EventGroupHandle_t wifi_event_group;
const int CONNECTED_BIT = BIT0;

static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    }

    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
    	ESP_LOGI(__func__, "Tentando reconexão.");
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
    }

    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(__func__, "Endereço IP obtido: " IPSTR, IP2STR(&event->ip_info.ip));
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
    }
}

static void flash_init(void)
{
	// Initialize NVS (Non-Volatile Storage) flash
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
}

/* Função para inicialização da conexão Wi-Fi */
static void wifi_init(void)
{
    wifi_event_group = xEventGroupCreate();

    // Initialize WiFi
	ESP_ERROR_CHECK(esp_netif_init());
	ESP_ERROR_CHECK(esp_event_loop_create_default());
	esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
	assert(sta_netif);
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL, &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL, &instance_got_ip));

    wifi_config_t wifi_config = {
		.sta = {
			.ssid = WIFI_SSID,
			.password = WIFI_PASS,
		},
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Wi-Fi STA iniciado. Conectando ao SSID: %s", WIFI_SSID);
}

/* Callback para sucesso de ping */
static void ping_success_callback(esp_ping_handle_t hdl, void *args)
{
    uint32_t elapsed_time;
    esp_ping_get_profile(hdl, ESP_PING_PROF_TIMEGAP, &elapsed_time, sizeof(elapsed_time));
    ESP_LOGI("check_latency", "Ping: %" PRIu32 " ms", elapsed_time);

    if(ping_count < pings){
    	latency[ping_count] = elapsed_time;
    	ping_count ++;
    }
}

/* Função para medir a latência usando ping */
static void check_latency(void)
{
	uint32_t medLatency = 0;
    esp_ping_config_t config = ESP_PING_DEFAULT_CONFIG();
    config.count = pings;

    ip_addr_t target_addr;
    inet_pton(AF_INET, "8.8.8.8", &target_addr.u_addr.ip4);
    target_addr.type = IPADDR_TYPE_V4;
    config.target_addr = target_addr;

    esp_ping_callbacks_t cbs;
    memset(&cbs, 0, sizeof(cbs));
    cbs.on_ping_success = ping_success_callback;
    cbs.on_ping_end = NULL;  // Evita cálculo duplicado na função de finalização

    esp_ping_handle_t ping;
    ESP_ERROR_CHECK(esp_ping_new_session(&config, &cbs, &ping));
    esp_ping_start(ping);

    // Espera até que o ping termine antes de continuar
	vTaskDelay(pdMS_TO_TICKS(pings * 1000));  // Espera até que o número de pings termine (aproximadamente 1 segundo por ping)

	esp_ping_stop(ping);
    esp_ping_delete_session(ping);

    ping_count = 0;
    for(int i = 0; i < pings; i++) medLatency += latency[i];
    medLatency = medLatency/pings;

    ESP_LOGI(__func__, "Latency: %" PRIu32 " ms", medLatency);

    strcpy(post_data, "");  // Inicializa o buffer de dados
    char ap_data[32];
    snprintf(ap_data, sizeof(ap_data), "Latency: %" PRIu32 " ms", medLatency);
	strcat(post_data, ap_data);
}

/* Função para varredura de redes Wi-Fi e criação dos dados a serem enviados */
static void wifi_scan(void)
{
	wifi_scan_config_t scan_config = {
		.ssid = (uint8_t *)target_SSID,
		.bssid = 0,
		.channel = 0,
		.show_hidden = true,
		.scan_type = WIFI_SCAN_TYPE_ACTIVE,
		.scan_time.active = {
			.min = 100,
			.max = 1000
		}
	};

    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));

    uint16_t ap_count = 0;
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    ESP_LOGI(__func__, "Total APs scanned = %" PRIu16, ap_count);

    if (ap_count == 0) {
    	return;
    }

    wifi_ap_record_t ap_info[ap_count];
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count, ap_info));

    strcpy(post_data, "");  // Inicializa o buffer de dados
	for (int i = 0; i < ap_count; i++) {
		char ap_data[128];
		snprintf(ap_data, sizeof(ap_data), "SSID: %s, RSSI: %d", ap_info[i].ssid, ap_info[i].rssi);
		strcat(post_data, ap_data);
	}

    ESP_LOGI(__func__, "Dados da varredura Wi-Fi preparados para envio.");
}

/* Função para enviar a mensagem HTTP */
static void http_send_data(void)
{
    esp_http_client_config_t config = {
            .url = SERVER_URL,
            .method = HTTP_METHOD_POST,
            .event_handler = NULL,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);

    esp_http_client_set_post_field(client, post_data, strlen(post_data));

    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(__func__, "Dados enviados com sucesso");
    } else {
        ESP_LOGE(__func__, "Erro durante o envio dos dados: %s", esp_err_to_name(err));
    }

    esp_http_client_cleanup(client);
}


/* Tarefa para realizar varredura e envio de dados periodicamente */
void scan_and_send_task(void *pvParameters)
{
    while (1) {
        wifi_scan();
        http_send_data();
        check_latency();
        http_send_data();
    }
}

void app_main(void)
{
	flash_init();
    wifi_init();

    /* Aguarda até que a conexão seja estabelecida (bit CONNECTED_BIT definido pelo evento do Wi-Fi) */
    EventBits_t bits = xEventGroupWaitBits(
    		wifi_event_group,
            CONNECTED_BIT,
            pdFALSE,
            pdTRUE,
            portMAX_DELAY);

    if (bits & CONNECTED_BIT) {
        ESP_LOGI(TAG, "Conectado ao AP, endereço IP obtido. Realizando varredura e enviando dados...");
        xTaskCreate(scan_and_send_task, "scan_and_send_task", 4096, NULL, 5, NULL);
    } else {
        ESP_LOGE(TAG, "Falha ao conectar ao AP");
    }
}
