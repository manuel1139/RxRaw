/* 
 * File:   remote.h
 * Author: manuel
 *
 * Created on 2. September 2016, 18:01
 */

#ifndef REMOTE_H
#define	REMOTE_H

#include <xc.h>
#include <stdint.h>

#include "remote_keys.h"

enum fsm_state {
    idle,
    header_a,
    header_b,
    first_edge,
    second_edge,
    done,
    not_me
};

struct remote;

typedef void (*pRxFunc)(struct remote*, uint16_t);

extern void ir_rx(struct remote*, uint16_t);
extern void ir_rx_pulse_space(struct remote*, uint16_t);

struct remote {
    const char* name;
    uint16_t hdr_time_a;
    uint16_t hdr_time_b;
    uint16_t low_1;
    uint16_t high_1;
    uint16_t low_0;
    uint16_t high_0;
    uint16_t pre_code;
    uint8_t bit_cnt;
    pRxFunc rx_func;
    const uint16_t *keys;
    enum fsm_state state;
};

const uint16_t terratec_ir_rc_codes[] = {
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, 
    KEY_6, KEY_7, KEY_8, KEY_9 
};

struct remote terratec_ir_rc = {
     "Terratec",
    0x3575, //header_a
    0x199C, //header_b
    0, //low_1
    0, //high_1
    0,
    0,
    0x28D7, //pre_code
    32,
    &ir_rx,
    &terratec_ir_rc_codes[0],
    idle
}; //codes

const uint16_t pollin_rf_rc_codes[] = {
    S1_ON,
    S1_OFF,
    S2_ON, 
    S2_OFF,
};

struct remote pollin_rf_rc = {
    "Pollin",
    0x0, //header_a
    0x3F0, //header_b
    0x43F, //low_1
    0x7B2, //high_1
    0x3C8, //low_0
    0x829, //high_0
    0x0B, //pre_code
    20, //bit count
    0,
    &pollin_rf_rc_codes[0], //codes
    idle
};


struct remote yamaha_ir_rc = {
    "Yamaha",
    0x3518, //header_a
    0x19B5, //header_b
    0x3D8, //low_1
    0x2A2, //high_1
    0x3D8, //low_0
    0x940, //high_0
    0x0BCD, //pre_code
    67, //bit count
    &ir_rx_pulse_space,
    &pollin_rf_rc_codes[0], //codes
    idle
};

#endif	/* REMOTE_H */
