#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "main.h"
#include "buttons.h"
#include "termometro.h"

#ifdef LOG
#include <stdio.h>
#include "usart.h"
#endif // LOG

/******************************************************************************/
struct fsm_handle
{
    uint8_t (*const fsmApply)(fsm_handleType *fsmh);
    uint8_t (*const fsmNext)(fsm_handleType *fsmh);
    volatile uint16_t timer;
    union
    {
        uint8_t all;
        struct
        {
            volatile uint8_t timeout : 1;
            uint8_t step_mode : 1;
            uint8_t status : 1;
        };
    } flags;
};

/******************************** ADICIONE A FSM AQUI *************************/
#define N_FSM 2
static fsm_handleType fsms[N_FSM] = {
    {.fsmApply = buttons_StateCall, .fsmNext = buttons_StateNext, .flags = {.status = 1}},
    {.fsmApply = termo_process, .fsmNext = termo_next, .flags = {.status = 1}},
};

/******************************* STATIC DECLARATIONS **************************/
volatile fsm_eventsType fsm_eventsWrite;
static volatile fsm_eventsType fsm_eventsRead;
volatile const fsm_eventsType *volatile const fsm_events = &fsm_eventsRead;

int main(void)
{
    /**** INICIALIZAÇÔES ****/
    // Mode 4 - TCC - OCRA
    TCCR1A = 0;
    TCCR1B = (1 << CS10) | (1 << WGM12);
    // 16Mhz/1/16000 = 1kHz -> 1ms
    OCR1A = 16000;
    TIMSK1 = (1 << OCIE1A);

    buttons_Init();

#ifdef LOG
    FILE *usart = USART_Init(B9600);
#endif // LOG

    set_sleep_mode(SLEEP_MODE_IDLE);
    sei();

    while (1)
    {
        uint8_t any_pool = 0;
        for (uint8_t i = 0; i < N_FSM; i++)
        {
            fsm_handleType *fsm = &fsms[i];
            if (fsm->flags.status == FSM_STATE_STATUS_CHANGED)
            {
                fsm_ResetTimeout(fsm);
                uint8_t step_mode = fsm->fsmApply(fsm);
                fsm->flags.step_mode = step_mode;
                if (step_mode == FSM_STEP_MODE_POOL)
                {
                    any_pool = 1;
                }
            }
        }

        cli();
        while (fsm_eventsWrite.all == 0 && any_pool == 0)
        {
            sei();
            sleep_mode();
        }

        cli();
        fsm_eventsRead.all = fsm_eventsWrite.all;

#ifdef LOG
        fprintf(usart, "t: %d > 0b", termo_temperatura);
        for (uint8_t i = 0; i < 32; i++)
            fprintf(usart, "%c", fsm_eventsRead.all & (1 << i) ? '1' : '0');
        fprintf(usart, "\n");
#endif
        fsm_eventsWrite.all = 0;
        sei();

        for (uint8_t i = 0; i < N_FSM; i++)
        {
            fsm_handleType *fsm = &fsms[i];
            uint8_t status = fsm->fsmNext(fsm);
            fsm->flags.status = status;
        }
    }
}

void fsm_SetTimeout(fsm_handleType *fsmh, uint16_t ms)
{
    fsmh->timer = 0;
    fsmh->flags.timeout = 0;
    fsmh->timer = ms;
}

void fsm_ResetTimeout(fsm_handleType *fsmh)
{
    fsmh->timer = 0;
    fsmh->flags.timeout = 0;
}

uint8_t fsm_TimedOut(fsm_handleType *fsmh)
{
    return fsmh->flags.timeout;
}

ISR(TIMER1_COMPA_vect)
{
    for (uint8_t i = 0; i < N_FSM; i++)
    {
        if (fsms[i].timer > 0)
        {
            fsms[i].timer -= 1;
            if (fsms[i].timer == 0)
            {
                fsm_eventsWrite.timeout = 1;
                fsms[i].flags.timeout = 1;
            }
        }
    }
}
