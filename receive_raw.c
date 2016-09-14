#include <xc.h>

#include "timer.h"
#include "capture.h"

//file globals
char edges = 0;
uint8_t edge_cnt = 0;
#define MAX_EDGE 70
uint16_t edge_times[MAX_EDGE];

void rx_raw(uint16_t bit_time) {
    if (edge_cnt < MAX_EDGE) {
        edge_times[edge_cnt] = bit_time;
        edge_cnt++;
    }
}

void rx_raw_timeo() {
    if (edge_cnt != 0) {
        edges = edge_cnt;
        edge_cnt = 0;
    }
}

