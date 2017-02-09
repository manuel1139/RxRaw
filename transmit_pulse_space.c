#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "remote.h"
#include "timer_tx.h"
#include "system.h"
#include "pwm.h"

#include "capture.h"

extern uint8_t transmitter_state;

enum device_type {
    DT_RF433,
    DT_IR
} dt;

void dev_send(enum device_type dt) {
#if defined(__18F2550)
    if (dt == DT_RF433) {
        RF_OUT = RF_OUT ^ 1;
    } else if (dt == DT_IR) {
        TogglePWM(); //start sending 38khz pulse
    }
#else
    RF_OUT = RF_OUT ^ 1;
#endif
    LED1 ^= 1;
}

void tx_pulse_space(struct remote* r) {
    dt = DT_IR;
    switch (r->tx_state) {
        case idle:
            r->tx_state = header_a;
        case header_a:
            if (r->hdr_time_a != 0) {
                dev_send(dt);
                r->tx_state = header_b;
                WriteTxTimer(0xFFFF - r->hdr_time_a);
                break;
            }
        case header_b:
            dev_send(dt);
            r->tx_state = first_edge;
            WriteTxTimer(0xFFFF - r->hdr_time_b);
            break;
        case first_edge:
            dev_send(dt);
            if (r->tx_data.bit_cnt > 16) {
                r->tx_data.edge_a_bit = r->pre_code & (1 << (r->tx_data.bit_cnt - 16 - 1));
            } else {
                r->tx_data.edge_a_bit = r->tx_data.code_to_send & (1 << r->tx_data.bit_cnt - 1);
            }
            r->tx_state = second_edge;
            r->tx_data.edge_a_bit ? WriteTxTimer(0xFFFF - r->a_1) :
                    WriteTxTimer(0xFFFF - r->a_0);
            break;
        case second_edge:
            dev_send(dt);
            if (r->tx_data.bit_cnt > 0) {
                r->tx_data.bit_cnt--;
                r->tx_state = first_edge;
            } else {
                r->tx_state = tail;
            }
            r->tx_data.edge_a_bit ? WriteTxTimer(0xFFFF - r->b_1) :
                    WriteTxTimer(0xFFFF - r->b_0);
            break;
        case tail:
            RF_OUT = 0; //last edge must be low
            //todo
#if defined(__18F2550)
            StopPWM();
#endif
            WriteTxTimer(0x0F00); //trailing pulse       
            r->tx_state = done;
            break;
        case done:
            r->init_tx(r);
            transmitter_state = 0;
            OpenRxCapture(CAP_EVERY_FALL_EDGE); //todo
            break;
        default:
            break;
    }
}


