#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "remote.h"
#include "timer.h"
#include "system.h"

static inline uint16_t reverse(uint16_t data, int bits)
{
        int i;
        uint16_t c;

        c = 0;
        for (i = 0; i < bits; i++)
                c |= (uint16_t)(((data & (((uint16_t)1) << i)) ? 1 : 0))
                        << (bits - 1 - i);
        return c;
}

void tx_pulse_space(struct remote* r, uint16_t key) {
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
            if (r->bit_cnt > 15) {
                r->tx_data.edge_a_bit = r->pre_code & (1 << r->bit_cnt - 16);
            } else {
                r->tx_data.edge_a_bit = key & (1 << r->bit_cnt);
            }
            r->state = second_edge;
            if (r->tx_data.edge_a_bit) WriteTxTimer(0xFFFF - r->high_1);
            else {
                WriteTxTimer(0xFFFF - r->low_0);
            }
            break;
        case second_edge:
            RF_OUT = ~RF_OUT;
            if (r->tx_data.edge_a_bit) WriteTxTimer(0xFFFF - r->low_1);
            else {
                WriteTxTimer(0xFFFF - r->high_0);
            }
            if (r->bit_cnt > 0) {
                r->bit_cnt--;
                r->state = first_edge;
            } else {
                r->state = done;
            }
            break;
        case done:
            RF_OUT = 0; //last edge must be  zero
            r->bit_cnt = 19;
            r->tx_data.edge_a_bit = 0;
            r->state = idle;
            break; 
        default:
            break;
    }
}


