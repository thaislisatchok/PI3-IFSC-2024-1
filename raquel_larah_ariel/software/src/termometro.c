#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "termometro.h"
#include "main.h"
#include "ds18b20/ds18b20.h"

int16_t termo_temperatura;

typedef enum
{
    TST_IDLE,
    TST_START_CONV,
    TST_READ,
    TST_ERROR,
} termo_stateType;
static termo_stateType termo_curr_state = TST_IDLE;

uint8_t termo_process(fsm_handleType *fsmh)
{
    uint8_t err;
    switch (termo_curr_state)
    {
    case TST_IDLE:
        termo_StartRead(); // isso é temporário
        break;

    case TST_START_CONV:
        err = ds18b20convert(&TERMO_PORT, &TERMO_DDR, &TERMO_PORTIN, TERMO_MASK, NULL);
        if (err)
            fsm_eventsWrite.termo.error = 1;
        fsm_SetTimeout(fsmh, 1000);
        break;

    case TST_READ:
        err = ds18b20read(&PORTB, &DDRB, &PINB, (1 << PINB0), NULL, &(termo_temperatura));
        if (err)
            fsm_eventsWrite.termo.error = 1;
        termo_temperatura /= 16;
        fsm_eventsWrite.termo.new = 1;
        break;

    case TST_ERROR:
        /*mostra o erro de alguma forma*/
        break;

    default:
        return 1;
    }
    return FSM_STEP_MODE_EVENT;
}

uint8_t termo_next(fsm_handleType *fsmh)
{
    if (fsm_events->termo.error)
    {
        if (termo_curr_state == TST_ERROR)
        {
            return FSM_STATE_STATUS_STEADY;
        }
        termo_curr_state = TST_ERROR;
        return FSM_STATE_STATUS_CHANGED;
    }

    switch (termo_curr_state)
    {
    case TST_IDLE:
        if (!fsm_events->termo.enable)
            return FSM_STATE_STATUS_STEADY;
        termo_curr_state = TST_START_CONV;
        return FSM_STATE_STATUS_CHANGED;

    case TST_START_CONV:
        if (!fsm_TimedOut(fsmh))
            return FSM_STATE_STATUS_STEADY;
        termo_curr_state = TST_READ;
        return FSM_STATE_STATUS_CHANGED;

    case TST_READ:
        termo_curr_state = TST_START_CONV;
        return FSM_STATE_STATUS_CHANGED;

    case TST_ERROR:
        return FSM_STATE_STATUS_STEADY;

    default:
        termo_curr_state = TST_ERROR;
        return FSM_STATE_STATUS_CHANGED;
    }
    return FSM_STATE_STATUS_CHANGED;
}

void termo_StartRead()
{
    fsm_eventsWrite.termo.enable = 1;
}
