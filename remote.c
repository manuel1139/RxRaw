#include "remote.h"

void init(struct remote *r);

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
    &init,
    &ir_rx_pulse_space, //rx_func
    0,  //tx_func
    &terratec_ir_rc_codes[0],
    idle,

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
    0x03F0, //header_b
    0x043F, //low_1
    0x07B2, //high_1
    0x03C8, //low_0
    0x0829, //high_0
    0x000B, //pre_code
    20, //bit count
    &init,
    0,      //rx_func
    &tx_pulse_space,    //tx_func
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
    &init,  //init_func
    &ir_rx_pulse_space,  //rxFunc
    0, //tx_func
    0, //codes
    idle
};


struct remote *remotes[] = { 
    &terratec_ir_rc, 
    &yamaha_ir_rc,
    &pollin_rf_rc,
    0
            //{}
};

void init(struct remote *r){
    r->rx_data.edge_a = 0;
    r->rx_data.word_cnt = 0;
    r->rx_data.bit_cnt = 0;
    r->rx_data.word[0] = 0;    //todo: allow for other size?  
    r->rx_data.word[1] = 0;    //todo: allow for other size?  

    r->tx_data.word_cnt = 2;
    r->tx_data.bit_cnt = r->bit_cnt;
    r->tx_data.edge_a_bit = 0;
}

