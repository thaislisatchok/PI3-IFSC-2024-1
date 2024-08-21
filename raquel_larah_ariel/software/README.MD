```mermaid
---
title: TTITLE
---
stateDiagram-v2
%, text-decoration-line:underline, text-decoration-style:double,text-underline-position:under
    classDef center text-align:center, ::first-line{font-weight:bold, font-size:large};
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    IDLE:::center:IDLE\n- PCINT enable
    DELAY_OK:::center:DELAY_OK\n- start timer\n- set mask to OK
    POOL_OK:::center
    DELAY_DW:::center:DELAY_DW\n- start timer\n- set mask to DW
    POOL_DW:::center
    DW_BURST:::center:DW_BURST\n- start timer\n- emit ev->dw_pressed
    DELAY_UP:::center:DELAY_UP\n- start timer\n- set mask to UP
    POOL_UP:::center
    UP_BURST:::center:UP_BURST\n- start timer\n- emit ev->up_pressed

    state " " as DW_HOLD {
        [*] --> POOL_DW
        POOL_DW --> DW_BURST : after 2s
        DW_BURST --> DW_BURST : after 1s
    }

    state " " as UP_HOLD {
        [*] --> POOL_UP
        POOL_UP --> UP_BURST : after 2s
        UP_BURST --> UP_BURST : after 1s
    }

    state POOLING_CHOICE <<choice>>
    state BURST_CHOICE <<choice>>

    state Botões {
        [*] --> IDLE
        IDLE --> DELAY_OK : ev->ok_pressed
        IDLE --> DELAY_DW : ev->dw_pressed
        IDLE --> DELAY_UP : ev->ok_pressed

        DELAY_OK --> SET_HOLD_TIMER : after 80 ms
        DELAY_DW --> SET_HOLD_TIMER : after 80 ms
        DELAY_UP --> SET_HOLD_TIMER : after 80 ms

        SET_BURST_TIMER --> BURST
        BURST --> SET_BURST_TIMER : after BURST_TIMER == 0
        BURST --> BURST_CHOICE
        BURST_CHOICE --> IDLE : GPIO & mask == 0
        BURST_CHOICE --> BURST : GPIO & mask != 0

        SET_HOLD_TIMER --> POOLING
        POOLING --> SET_BURST_TIMER : after HOLD_TIMER == 0
        POOLING --> POOLING_CHOICE
        POOLING_CHOICE --> IDLE : GPIO & mask == 0
        POOLING_CHOICE --> POOLING : GPIO & mask != 0
    } 


    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    TST_IDLE:::center: IDLE\n
    TST_START_CONV:::center: START_CONV\n- ds18b20convert\n- start timer
    TST_READ:::center: READ\n- ds18b20read\n- temperatura = read/16\n- emit event
    TST_ERROR:::center: ERROR\n

    state " " as Termometro_Active {
        [*] --> TST_START_CONV
        TST_START_CONV --> TST_READ : after 1s
        TST_READ --> TST_START_CONV
    }

    state Termometro {
        [*] --> TST_IDLE
        TST_IDLE --> Termometro_Active : enable = true
        Termometro_Active --> TST_IDLE : enable = false
        Termometro_Active --> TST_ERROR : error != 0
    }

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    state " " as Main {
        Botões
        --
        Termometro
    } 
    Main
```