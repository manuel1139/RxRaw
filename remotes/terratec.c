#include "remote.h"

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
    0, //tail
    0x28D7, //pre_code
    32,
    &init_rx,
    &init_tx,
    &ir_rx_pulse_space, //rx_func
    0, //tx_func
    &terratec_ir_rc_codes[0],
    idle
}; //codes

struct remote terratec_ir_rc;
