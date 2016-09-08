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



bool ibb(uint16_t remote_time, uint16_t bit_time) {
    uint16_t diff;
    diff = remote_time >> 7;
    
    if (remote_time < bit_time + diff && remote_time > bit_time - diff) {
        return true;
    }
    return false;
}

void ir_rx_pulse_space(struct remote* r, uint16_t bit_time) {
    static uint16_t l_first_edge;
    uint16_t current_code;
    uint16_t diff;
    static uint8_t bit_cnt = 0;
    static uint8_t byte_cnt = 0;
    static uint8_t data[4];
    
    switch ( r->state) {
        case idle: //ignore first edge
             r->state = header_a;
            break;
        case header_a:
            //allow 1/16 bit time as difference
            ibb(r->hdr_time_a, bit_time) ? r->state = header_b :
                r->state = not_me;                  
            break;
        case header_b:
            ibb(r->hdr_time_b, bit_time) ? r->state = first_edge :
                r->state = not_me;                  
            break;
        case first_edge:
            ibb(r->high_0, bit_time) ? r->state = second_edge :
                r->state = not_me;                  
            break;
        case second_edge:
            ibb(r->high_1, bit_time) ? r->state = first_edge :
                r->state = not_me;                  

            if (bit_cnt < r->bit_cnt) {
                if (first_edge > second_edge) {
                    data[byte_cnt] << 1;
                    data[byte_cnt] |= 1;
                } else {
                    data[byte_cnt] << 1;
                }   
            } else {
                bit_cnt = 0;
                byte_cnt = 0;
                //reset_fsm(& ir_ps_fsm);                
            }
            break;
        case not_me:
            break;
        default:
            break;

    }
}