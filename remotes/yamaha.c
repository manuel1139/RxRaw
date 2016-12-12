#include "remote.h"

const uint16_t yamaha_codes[] = {
    Y_VOL_UP, // vol. up
    Y_VOL_DOWN,
};

struct remote yamaha_ir_rc = {
    "Yamaha",
    0x3518, //header_a
    0x19B5, //header_b
    0x361, //a_1  
    0x2A5, //b_1 
    0x361, //a_0
    0x91A, //b_0
    0x0, //tail    
    0xA15E, //
    32, //bit count
    &init_rx,
    &init_tx,
    &ir_rx_pulse_space, //rxFunc
    &tx_pulse_space, //tx_func
    &yamaha_codes[0], //codes
    idle
};

struct remote yamaha_ir_rc;
