#include "remote.h"

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
    0, //tail
    0xFF08, //pre_code
    32,
    &init_rx,
    &init_tx,
    &ir_rx_pulse_space, //rx_func
    0, //tx_func
    &minfiniy_led_codes,
    idle
};

