#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "remote.h"

void ir_rx(struct remote* p_ir_rc, uint16_t bit_time) {
    static uint16_t l_first_edge;
    struct remote ir_rc = *p_ir_rc;
    uint16_t *dp;
    uint16_t current_code;
    static uint8_t bit_cnt = 0;
    /*
        switch (ir_rx_fsm.state) {
            case idle: //ignore first edge
                ir_rx_fsm.state = header_a;
                break;
            case header_a:
                ir_rc.hdr_time_a = bit_time;
                ir_rx_fsm.state = header_b;
                break;
            case header_b:
                ir_rc.hdr_time_b = bit_time;
                ir_rx_fsm.state = first_edge;
                break;
            case first_edge:
                l_first_edge = bit_time;
                ir_rx_fsm.state = second_edge;
                break;
            case second_edge:
                if (bit_cnt < 15) {
                    dp = &(ir_rc.pre_code);
                } else if (bit_cnt > 15 &&
                        bit_cnt < 31) {
                    dp = &(current_code);
                }

     *dp <<= 1;
                if (l_first_edge > bit_time) {
     *dp |= 1;
                }

                if (bit_cnt < 31) {
                    bit_cnt++;
                    ir_rx_fsm.state = first_edge;
                } else {
                    //try to find code in rc
                }
                bit_cnt = 0;
                //reset_fsm(&ir_rx_fsm);

                break;
            default:
                break;

        }  */
}

bool chk_bit_bounds(struct remote* r, uint16_t a, uint16_t b) {

    uint16_t diff_a, diff_b;
    bool ok = false;
    
    diff_a = a >> 3;
    diff_b = b >> 3;

    ok = 1;
    ok = (r->low_1 < a + diff_a ) ;
    ok = (r->low_1 > a - diff_a);
    ok = (r->high_1 < b + diff_b && r->high_1 > b - diff_b);
    ok = (r->low_0 < a    + diff_a && r->low_0 > a - diff_a);            
    ok = (r->high_0 < b + diff_b && r->high_0 > b - diff_b);          
    /*
            if (((r->low_1 < a + diff_a && r->low_1 > a - diff_a) &&
            (r->high_1 < b + diff_b && r->high_1 > b - diff_b)) ||
            ((r->low_0 < a    + diff_a && r->low_0 > a - diff_a) &&
            (r->high_0 < b + diff_b && r->high_0 > b - diff_b))) */

    
    return true;
}

bool chk_hdr_bounds(uint16_t remote_time, uint16_t bit_time) {
    uint16_t diff;
    diff = remote_time >> 3; //debug only

    if (remote_time < bit_time + diff && remote_time > bit_time - diff) {
        return true;
    }
    return false;
}

void ir_rx_pulse_space(struct remote* r, uint16_t bit_time) {
    uint16_t current_code;
    uint16_t diff;
    
    switch (r->state) {
        case idle: //ignore first edge
            r->state = header_a;
            break;
        case header_a:
            //allow 1/16 bit time as difference
            chk_hdr_bounds(r->hdr_time_a, bit_time) ? r->state = header_b :
                    r->state = not_me;
            break;
        case header_b:
            chk_hdr_bounds(r->hdr_time_b, bit_time) ? r->state = first_edge :
                    r->state = not_me;
            break;
        case first_edge:
            r->rx_data.edge_a = bit_time;
            r->state = second_edge;
            break;
        case second_edge:
            chk_bit_bounds(r, r->rx_data.edge_a, bit_time) ?
                    r->state = first_edge : r->state = not_me;
            if (r->state == not_me) break;

            if (r->rx_data.word_cnt < 2) {
                if (r->rx_data.bit_cnt < 16) {
                    r->rx_data.word[r->rx_data.word_cnt] <<= 1;
                    if (r->rx_data.edge_a > bit_time) {
                        r->rx_data.word[r->rx_data.word_cnt] |= 1;
                    }
                    r->rx_data.bit_cnt++;
                } else {
                    r->rx_data.bit_cnt = 0;
                    r->rx_data.word_cnt++;
                }
            }

            //check if code found

            break;
        case not_me:
            break;
        default:
            break;

    }
}