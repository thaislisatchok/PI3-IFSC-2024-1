#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
#include <stdint.h>

#define FSM_STEP_MODE_EVENT 0
#define FSM_STEP_MODE_POOL 1

#define FSM_STATE_STATUS_STEADY 0
#define FSM_STATE_STATUS_CHANGED 1

typedef union
{
    uint32_t all;
    struct
    {
        uint8_t timeout : 1;
        union
        {
            uint8_t all;
            struct
            {
                uint8_t new : 1;
                uint8_t enable : 1;
                uint8_t error : 1;
            };
        } termo;

        union
        {
            uint8_t all;
            struct
            {
                uint8_t ok : 1;
                uint8_t dw : 1;
                uint8_t up : 1;
                uint8_t _ext : 1;
            };
        } buttons;
    };
} fsm_eventsType;

typedef struct fsm_handle fsm_handleType;

extern volatile fsm_eventsType fsm_eventsWrite;
extern volatile const fsm_eventsType *volatile const fsm_events;

void fsm_SetTimeout(fsm_handleType *fsmh, uint16_t ms);
void fsm_ResetTimeout(fsm_handleType *fsmh);
uint8_t fsm_TimedOut(fsm_handleType *fsmh);

#endif
