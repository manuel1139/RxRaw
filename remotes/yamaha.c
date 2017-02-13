#include "remote.h"

const uint16_t yamaha_codes[] = {
    Y_VOL_UP, // vol. up
    Y_VOL_DOWN,
};

struct remote yamaha_ir_rc = {
    "Yamaha",
    //counter to tail are in us
    9000, //header_a in us
    4500, //header_b
    460, //a_1  
    520, //b_1 
    520, //a_0
    1600, //b_0
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
