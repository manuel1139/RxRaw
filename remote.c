#include "remote.h"

void init_rx(struct remote *r);
void init_tx(struct remote *r);

#define MF_KEY1 0xDF20
#define MF_KEY2 0xEF10

const uint16_t minfiniy_led_codes[] = {
    MF_KEY1, MF_KEY2
};

struct remote minfiniy_led = {
    "Minfiny LED RGB 5050",
    0x3504, //header_a
    0x19CD, //header_b
    0x0392, //a_1
    0x029B, //b_1
    0x0394, //a_0
    0x0914, //b_0
    0,      //tail
    0xFF08, //pre_code
    32,
    &init_rx,
    &init_tx,
    &ir_rx_pulse_space, //rx_func
    0, //tx_func
    &minfiniy_led_codes,
    idle
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
    0,  //tail
    0x28D7, //pre_code
    32,
    &init_rx,
    &init_tx,
    &ir_rx_pulse_space, //rx_func
    0, //tx_func
    &terratec_ir_rc_codes[0],
    idle
}; //codes

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


const uint16_t yamaha_codes[] = {
    Y_VOL_UP,  // vol. up
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
    0x0,    //tail    
    0xA15E, //
    32, //bit count
    &init_rx,
    &init_tx,
    &ir_rx_pulse_space, //rxFunc
    &tx_pulse_space, //tx_func
    &yamaha_codes[0], //codes
    idle
};

enum e_remotes{
    TERRATEC = 0,
    YAMAHA,
    POLLIN,
    MINFINIY,
    REMOTES_MAX
};
struct remote *remotes[REMOTES_MAX] = {
    &terratec_ir_rc,
    &yamaha_ir_rc,
    &pollin_rf_rc,
    &minfiniy_led,
&minfiniy_led,            
    0
    //{}
};

// remotes[TERRATEC], key ->  function

void init_rx(struct remote *r) {
    r->rx_state = idle;  
    r->rx_data.edge_a = 0;
    r->rx_data.word_cnt = 0;
    r->rx_data.bit_cnt = 0;
    r->rx_data.word[0] = 0; //todo:
    r->rx_data.word[1] = 0; 
}

void init_tx(struct remote *r) {
    r->tx_state = idle;  
    r->tx_data.word_cnt = 2;
    r->tx_data.bit_cnt = r->bit_cnt;
    r->tx_data.edge_a_bit = 0;
    r->tx_data.code_to_send = 0;   
}