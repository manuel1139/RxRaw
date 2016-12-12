#include "remote.h"

const uint16_t pollin_rf_rc_codes[] = {
    S1_ON,
    //    S1_OFF,
    S2_ON,
    S2_OFF,
    S3_ON,
    S3_OFF,
    STEST,
};


struct remote pollin_rf_rc = {
    "Pollin",
    0x0, //header_a
    0x03F0, //header_b
    0x043F, //low_1
    0x07B2, //high_1
    0x03C8, //low_0
    0x0829, //high_0
    0xF000, //tail
    0x000B, //pre_code
    20, //bit count
    &init_rx,
    &init_tx,
    0, //rx_func
    &tx_pulse_space, //tx_func
    &pollin_rf_rc_codes[0], //codes
    idle
};

struct remote pollin_rf_rc;
