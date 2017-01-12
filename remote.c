#include "remote.h"

void init_rx(struct remote *r) {
    r->rx_state = idle;
    r->rx_data.edge_a = 0;
    r->rx_data.word_cnt = 0;
    r->rx_data.bit_cnt = 0;
    r->rx_data.code_found = 0;
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