#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "remote.h"
#include "timer.h"
#include "system.h"

void tx_pulse_space(struct remote* r) {
    switch (r->state) {
        case idle: //not needed in tx
            r->state = header_a;
        case header_a:
            if (r->hdr_time_a != 0) {
                RF_OUT = ~RF_OUT;
                r->state = header_b;
                WriteTxTimer(0xFFFF - r->hdr_time_a);
                break;
            }
        case header_b:
            RF_OUT = ~RF_OUT;
            r->state = first_edge;
            WriteTxTimer(0xFFFF - r->hdr_time_b);
            break;
        case first_edge:
            RF_OUT = ~RF_OUT;
            if (r->tx_data.bit_cnt > 16) {
                r->tx_data.edge_a_bit = r->pre_code & (1 << (r->tx_data.bit_cnt - 16 - 1));
            } else {
                r->tx_data.edge_a_bit = r->tx_data.code_to_send & (1 << r->tx_data.bit_cnt - 1);
            }
            r->state = second_edge;
            r->tx_data.edge_a_bit ? WriteTxTimer(0xFFFF - r->high_1) :
                WriteTxTimer(0xFFFF - r->low_0);
            break;
        case second_edge:
            RF_OUT = ~RF_OUT;
            if (r->tx_data.bit_cnt > 1) {
                r->tx_data.bit_cnt--;
                r->state = first_edge;
            } else {
                r->state = tail;
            }
            r->tx_data.edge_a_bit ? WriteTxTimer(0xFFFF - r->low_1) :
                WriteTxTimer(0xFFFF - r->high_0);
            break;
        case tail:
            RF_OUT = 0; //last edge must be low
            WriteTxTimer(0x0F00);  //trailing pulse       
            r->state = done;
            break;
        case done:
            r->init(r);
            break;
        default:
            break;
    }
}


