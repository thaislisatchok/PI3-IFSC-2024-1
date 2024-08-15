**INSTITUTO FEDERAL DE SANTA CATARINA**

**Unidade Curricular:**  Projeto Integrador 3 

**Professor:**  Robinson Pizzio e Matheus Leitzke Pinto 

**Alunos:**  Natália Besen e Victor Lompa Schwider


#  Analisador de Sinal de Wi-fi

* [Introdução](#introdução)
* [Componentes utilizados](#componentes-utilizados)
* [Códigos implementados](#códigos-implementados)

## Introdução

O projeto do Analisador de Sinal de Wi-Fi visa desenvolver um dispositivo destinado a medir e mapear a intensidade do sinal Wi-Fi em um ambiente específico. A importância dessa ferramenta está na sua capacidade de identificar áreas com sinal fraco ou "pontos cegos" em uma rede sem fio, proporcionando informações valiosas para a otimização da conectividade.

Um dos principais objetivos deste projeto é realizar medições ponto a ponto do sinal Wi-Fi em diferentes locais do ambiente. Para isso, o usuário precisa percorrer o ambiente enquanto o dispositivo realiza as medições em tempo real.

Os dados obtidos serão representados em forma de mapa de calor. Esse mapa de calor oferece uma visualização intuitiva da distribuição do sinal Wi-Fi, destacando as áreas com sinal forte em cores quentes e as áreas com sinal fraco em cores frias. Essa visualização facilita a identificação rápida de áreas problemáticas e orienta a tomada de decisões para melhorar a cobertura da rede.

A identificação de "pontos cegos", ou seja, áreas onde o sinal Wi-Fi é insuficiente ou inexistente, é outra funcionalidade essencial do Analisador de Sinal de Wi-Fi. Essa capacidade permite que os usuários identifiquem áreas críticas que necessitam de intervenção para melhorar a conectividade, seja por meio de reposicionamento de dispositivos ou adoção de soluções de ampliação do alcance do sinal.

Além disso, o projeto visa atender às necessidades específicas das redes de roteadores mesh, amplamente utilizadas em residências e escritórios. Essas redes, compostas por vários dispositivos interconectados, demandam uma cobertura uniforme para garantir uma conexão estável em toda a residência. O Analisador de Sinal de Wi-Fi surge como uma resposta a essa demanda, oferecendo uma ferramenta poderosa para otimizar a localização desses dispositivos e garantir uma experiência de conectividade sem fio de alta qualidade.


## Componentes utilizados

 *   ESP32 Dev-Kit  
	 * Conectividade Wi-Fi Integrada
	 * Potência de Processamento
	 * Capacidades de Comunicação
     * Compatibilidade com Bibliotecas
     
     ![ESP32 Dev-Kit](https://grobotronics.com/images/detailed/123/esp32-4-1_grobo.jpg )
     
## Códigos implementados

### Medição da intensidade do sinal de Wi-Fi

Inicialmente foi implementado um código para realizar a medição do **RSSI** (Received Signal Strength Indication) de uma rede Wi-Fi especificada. O **RSSI** é uma medida da potência do sinal recebido por um dispositivo em uma rede Wi-Fi. Este parâmetro é tipicamente medido em decibéis relativos a um miliwatt (dBm) e é geralmente representado como um valor negativo. Quanto mais próximo de zero, mais forte é o sinal.
Por meio da função `wifi_scan` exibida a seguir é possível obter a informação de RSSI da rede Wi-Fi desejada.  
A função `wifi_scan` realiza as seguintes etapas:

1.  Configura a varredura Wi-Fi.
2.  Inicia a varredura e espera até que seja concluída.
3.  Obtém o número de APs encontrados.
4.  Se nenhum AP for encontrado, a função retorna.
5.  Obtém os registros dos APs encontrados.
6.  Prepara os dados formatados para cada AP encontrado e os armazena em um buffer.
7.  Registra no log que os dados foram preparados para envio.

 ``` C
 static  void  wifi_scan(void)
{
	wifi_scan_config_t  scan_config  =  {
		.ssid =  (uint8_t  *)target_SSID,
		.bssid =  0,
		.channel =  0,
		.show_hidden =  true,
		.scan_type =  WIFI_SCAN_TYPE_ACTIVE,
		.scan_time.active =  {
			.min =  100,
			.max =  1000
		}
	};

	ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config,  true));
	uint16_t  ap_count  =  0;
	ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
	ESP_LOGI(__func__,  "Total APs scanned = %" PRIu16, ap_count);
  
	if  (ap_count  ==  0)  {
		return;
	}
  
	wifi_ap_record_t  ap_info[ap_count];
	ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count,  ap_info));
	strcpy(post_data,  "");  // Inicializa o buffer de  dados

	for  (int  i  =  0;  i  <  ap_count;  i++)  {
		char  ap_data[128];
		snprintf(ap_data,  sizeof(ap_data),  "SSID: %s, RSSI: %d\n",  ap_info[i].ssid,  ap_info[i].rssi);
		strcat(post_data,  ap_data);
	}

	ESP_LOGI(__func__,  "Dados  da  varredura Wi-Fi preparados  para  envio.");

}
 ```

### Medição de Latência

A medição de latência também é importante para avaliar a qualidade do sinal Wi-Fi. **Latência** é o tempo que um pacote de dados leva para viajar de um ponto de origem a um ponto de destino e vice-versa. Dessa forma, foi implementado uma função que mede a latência da rede Wi-Fi enviando pings para o servidor DNS do Google (`8.8.8.8`). Ela utiliza callbacks para registrar o tempo de resposta de cada ping, calcula a latência média após a conclusão de todos os pings e prepara os dados para envio.
As função `ping_success_callback` e  `check_latency`demonstradas a seguir foram criadas para realizar a medição da latência.
A função `check_latency` realiza as seguintes etapas:

1. Inicialização dos dados.
2. Configuração do Endereço de Destino.
3. Configuração dos Callbacks.
4. Início da Sessão de Ping.
5. Aguarda Conclusão dos Pings.
6. Finaliza a Sessão de Ping
7. Cálculo da Latência Média
8. Log e Preparação dos Dados
   

 ```C
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
    medLatency = medLatency / pings;

    ESP_LOGI(__func__, "Latency: %" PRIu32 " ms", medLatency);

    strcpy(post_data, "");  // Inicializa o buffer de dados
    char ap_data[32];
    snprintf(ap_data, sizeof(ap_data), "Latency: %" PRIu32 " ms", medLatency);
    strcat(post_data, ap_data);
}

 ```

Enquanto a função `ping_success_callback` obtém o tempo decorrido (latência) do ping bem-sucedido e armazena o valor em array.
 ```C
 static  void  ping_success_callback(esp_ping_handle_t  hdl,  void  *args)

{
	uint32_t  elapsed_time;
	esp_ping_get_profile(hdl,  ESP_PING_PROF_TIMEGAP,  &elapsed_time,  sizeof(elapsed_time));
	ESP_LOGI("check_latency",  "Ping: %" PRIu32 " ms", elapsed_time);

	if(ping_count < pings){

		latency[ping_count]  =  elapsed_time;
		ping_count ++;

	}

}
 ```

### Criação de um servidor http

Para a coleta e o armazenamento de dados medidos pelo ESP32, foi implementado um servidor web simples utilizando Python e o framework Flask. Este servidor HTTP é capaz de receber dados enviados pelo ESP32 através de solicitações POST, processá-los e retornar uma confirmação de recebimento. Por meio do servidor é possível realizar o armazenamento e posterior análise dos dados recebidos.
O código do servidor será exibido a seguir:
```python
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
    if request.is_json:
        data = request.get_json()
    else:
        data = request.form.to_dict()
    print(f"Received data: {data}")
    # Aqui você pode salvar os dados em um banco de dados ou arquivo
    return jsonify({"status": "success"}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

```

### Envio dos dados via http

Para o envio dos dados obtidos de RSSI e latência medidos foi implementada a função `http_send_data`, conforme mostrado abaixo.
A função `http_send_data` realiza os seguintes passos:
1.  Configura o cliente HTTP com a URL do servidor e o método POST.
2.  Inicializa o cliente HTTP com a configuração especificada.
3.  Define os dados que serão enviados no corpo da requisição POST.
4.  Executa a requisição HTTP e verifica se foi bem-sucedida, logando o resultado.
5.  Limpa os recursos utilizados pelo cliente HTTP.

```C
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

```

### Código completo

O código implementado até o momento contendo as funções descritas acima pode ser acessado no link abaixo:
* [Código Implementado](./main.c)

