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
    uint16_t d;
    reverse(r->pre_code,4);
    
    switch (r->state) {
        case idle: //ignore first edge
            r->state = header_a;
            break;
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
            if (r->tx_data.word_cnt > 0) {
                if (r->tx_data.bit_cnt > 0 ) {
                    if (r->tx_data.word_cnt == 0) {
                        d = r->pre_code;
                    } else if (r->tx_data.word_cnt == 1) {
                        d = key;
                    }
                    
                    //    WriteTxTimer(0xFFFF - );
                     r->tx_data.bit_cnt--;
                }
                    r->tx_data.word_cnt--;}
            
                
            break;
        case second_edge:
            RF_OUT = ~RF_OUT;
/*            if (tmp) WriteTxTimer(0xFFFF - pollin_rf_rc.low_1);
            else {
                WriteTxTimer(0xFFFF - pollin_rf_rc.high_0);
            }
            if (bit_cnt > 0) {
                bit_cnt--;
                rf_tx_fsm.state = first_edge;
            } else {
                rf_tx_fsm.state = done;
            }*/
            break;
        case done:
/*            RF_OUT = 0; //last edge must be  zero
            bit_cnt = 19;
            rf_tx_fsm.state = idle;
            code_to_send.code = 0;
            code_to_send.rc = 0;
            break; */
        default:
            break;
    }
}


