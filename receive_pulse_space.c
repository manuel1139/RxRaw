#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "remote.h"

bool chk_bit_bounds(struct remote* r, uint16_t a, uint16_t b) {

    uint16_t diff_a, diff_b;
    bool a1, b1, a0, b0, x;

    diff_a = a >> 2;
    diff_b = b >> 2;

    a1 = (r->a_1 < a + diff_a) && (r->a_1 > a - diff_a); //first edge for 1
    b1 = (r->b_1 < b + diff_b && r->b_1 > b - diff_b); //second edge for 1
    a0 = (r->a_0 < a + diff_a && r->a_0 > a - diff_a); //first edge for 0            
    b0 = (r->b_0 < b + diff_b && r->b_0 > b - diff_b); //secode edge for 0

    x = (a1 && b1) || (a0 && b0); //todo: check for burst
    if (!x) {
        x++;
    }
    return x;
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
    switch (r->rx_state) {
        case idle: //ignore first edge
            r->rx_state = header_a;
            break;
        case header_a:
            //allow 1/16 bit time as difference
            chk_hdr_bounds(r->hdr_time_a, bit_time) ? r->rx_state = header_b :
                    r->rx_state = not_me;
            break;
        case header_b:
            chk_hdr_bounds(r->hdr_time_b, bit_time) ? r->rx_state = first_edge :
                    r->rx_state = not_me;
            break;
        case first_edge:
            r->rx_data.edge_a = bit_time;
            r->rx_state = second_edge;
            break;
        case second_edge:
            if (r->rx_data.bit_cnt < r->bit_cnt) {
                chk_bit_bounds(r, r->rx_data.edge_a, bit_time) ?
                        r->rx_state = first_edge : r->rx_state = not_me;
                if (r->rx_state == not_me) break;

                r->rx_data.word_cnt = r->rx_data.bit_cnt / 16;

                r->rx_data.word[r->rx_data.word_cnt] <<= 1;
                //TODO:: might NOT alwas work!
                if (r->rx_data.edge_a > bit_time) {

                    r->rx_data.word[r->rx_data.word_cnt] |= 1;
                }
                r->rx_data.bit_cnt++;
            } else {
                //todo: check bit count
                r->rx_data.code_found = r->rx_data.word[1];
                //                r->init(r);  //? wait  for next timeout
            }
            break;
        case not_me:
            break;
        default:
            break;

    }
}