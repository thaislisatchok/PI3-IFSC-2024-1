#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "main.h"
#include "buttons.h"

#define BUTTONS_OK() ((BUTTONS_OK_PINR & BUTTONS_OK_MASK))
#define BUTTONS_DW() ((BUTTONS_DW_PINR & BUTTONS_DW_MASK))
#define BUTTONS_UP() ((BUTTONS_UP_PINR & BUTTONS_UP_MASK))

typedef enum
{
    BST_IDLE,
    BST_DELAY_OK,
    BST_POOL_OK,
    BST_DELAY_DW,
    BST_POOL_DW,
    BST_DW_BURST,
    BST_DELAY_UP,
    BST_POOL_UP,
    BST_UP_BURST,
} buttons_stateType;

static void buttons_EnableExtInt();
static void buttons_DisableExtInt();
static void buttons_isr();

static buttons_stateType buttons_curr_state = BST_IDLE;

uint8_t buttons_StateCall(fsm_handleType *fsmh)
{
    switch (buttons_curr_state)
    {
    case BST_IDLE:
        buttons_EnableExtInt();
        return FSM_STEP_MODE_EVENT;
    case BST_DELAY_OK:
    case BST_DELAY_DW:
    case BST_DELAY_UP:
        fsm_SetTimeout(fsmh, 80);
        return FSM_STEP_MODE_EVENT;
    case BST_POOL_DW:
    case BST_POOL_UP:
        fsm_SetTimeout(fsmh, BUTTONS_HOLD_TIME_MS);
    case BST_POOL_OK:
        return FSM_STEP_MODE_POOL;
    case BST_DW_BURST:
        fsm_eventsWrite.buttons.dw = 1;
        fsm_SetTimeout(fsmh, BUTTONS_BURST_TIME_MS);
        return FSM_STEP_MODE_POOL;
    case BST_UP_BURST:
        fsm_eventsWrite.buttons.up = 1;
        fsm_SetTimeout(fsmh, BUTTONS_BURST_TIME_MS);
        return FSM_STEP_MODE_POOL;
    }
    return FSM_STEP_MODE_POOL;
}

uint8_t buttons_StateNext(fsm_handleType *fsmh)
{
    uint8_t timedout = fsm_TimedOut(fsmh);
    switch (buttons_curr_state)
    {
    case BST_IDLE:
        if (fsm_events->buttons.ok)
            buttons_curr_state = BST_DELAY_OK;
        else if (fsm_events->buttons.dw)
            buttons_curr_state = BST_DELAY_DW;
        else if (fsm_events->buttons.up)
            buttons_curr_state = BST_DELAY_UP;
        else
            return FSM_STATE_STATUS_STEADY;
        return FSM_STATE_STATUS_CHANGED;

    case BST_DELAY_OK:
        if (!timedout)
            return FSM_STATE_STATUS_STEADY;
        buttons_curr_state = BST_POOL_OK;
        return FSM_STATE_STATUS_CHANGED;

    case BST_POOL_OK:
        if (!BUTTONS_OK())
            return FSM_STATE_STATUS_STEADY;
        buttons_curr_state = BST_IDLE;
        return FSM_STATE_STATUS_CHANGED;

    case BST_DELAY_DW:
        if (!timedout)
            return FSM_STATE_STATUS_STEADY;
        buttons_curr_state = BST_POOL_DW;
        return FSM_STATE_STATUS_CHANGED;

    case BST_POOL_DW:
    case BST_DW_BURST:
        if (BUTTONS_DW())
        {
            buttons_curr_state = BST_IDLE;
            return FSM_STATE_STATUS_CHANGED;
        }
        if (timedout)
        {
            buttons_curr_state = BST_DW_BURST;
            return FSM_STATE_STATUS_CHANGED;
        }
        return FSM_STATE_STATUS_STEADY;

    case BST_DELAY_UP:
        if (!timedout)
            return FSM_STATE_STATUS_STEADY;
        buttons_curr_state = BST_POOL_UP;
        return FSM_STATE_STATUS_CHANGED;

    case BST_POOL_UP:
    case BST_UP_BURST:
        if (BUTTONS_UP())
        {
            buttons_curr_state = BST_IDLE;
            return FSM_STATE_STATUS_CHANGED;
        }
        if (timedout)
        {
            buttons_curr_state = BST_UP_BURST;
            return FSM_STATE_STATUS_CHANGED;
        }
        return FSM_STATE_STATUS_STEADY;
    }
    return 0;
}

void buttons_Init()
{
    BUTTONS_OK_DDR &= ~BUTTONS_OK_MASK;
    BUTTONS_OK_PORT |= BUTTONS_OK_MASK;

    BUTTONS_DW_DDR &= ~BUTTONS_DW_MASK;
    BUTTONS_DW_PORT |= BUTTONS_DW_MASK;

    BUTTONS_UP_DDR &= ~BUTTONS_UP_MASK;
    BUTTONS_UP_PORT |= BUTTONS_UP_MASK;

    PCICR |= (BUTTONS_UP_PCICR_MASK) | (BUTTONS_DW_PCICR_MASK) | (BUTTONS_OK_PCICR_MASK);

    buttons_EnableExtInt();
}

static void buttons_EnableExtInt()
{
    BUTTONS_OK_PCMSK |= BUTTONS_OK_MASK;
    BUTTONS_DW_PCMSK |= BUTTONS_DW_MASK;
    BUTTONS_UP_PCMSK |= BUTTONS_UP_MASK;
}

static void buttons_DisableExtInt()
{
    BUTTONS_OK_PCMSK &= BUTTONS_OK_MASK;
    BUTTONS_DW_PCMSK &= BUTTONS_DW_MASK;
    BUTTONS_UP_PCMSK &= BUTTONS_UP_MASK;
}

static void buttons_isr()
{
    if (!BUTTONS_OK())
    {
        fsm_eventsWrite.buttons.ok = 1;
        buttons_DisableExtInt();
        return;
    }
    if (!BUTTONS_DW())
    {
        fsm_eventsWrite.buttons.dw = 1;
        buttons_DisableExtInt();
        return;
    }
    if (BUTTONS_UP())
    {
        fsm_eventsWrite.buttons.up = 1;
        buttons_DisableExtInt();
        return;
    }
}

ISR(PCINT0_vect)
{
    buttons_isr();
}

ISR(PCINT1_vect)
{
    buttons_isr();
}

ISR(PCINT2_vect)
{
    buttons_isr();
}
