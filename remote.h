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
struct remote *remotes[];

typedef void (*pRxFunc)(struct remote*, uint16_t);
typedef void (*pTxFunc)(struct remote*,  uint16_t);

typedef void (*pInitFunc)(struct remote*);

extern void ir_rx(struct remote*, uint16_t);
extern void ir_rx_pulse_space(struct remote*, uint16_t);

extern void tx_pulse_space(struct remote*, uint16_t key);


typedef struct  {
    //for remote rcx
    uint16_t edge_a;
    uint8_t word_cnt;
    uint8_t bit_cnt;
    uint16_t word[2];    //todo: allow for other size?  
} rx_data;


typedef struct  {
    //for remote rcx
    uint8_t word_cnt;
    uint8_t bit_cnt;
    uint16_t word[2];    //todo: allow for other size?  
} tx_data;


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
    pInitFunc init;
    pRxFunc rx_func;
    pTxFunc tx_func;
    const uint16_t *keys;
    enum fsm_state state;
    
    rx_data rx_data;
    tx_data tx_data;
};

struct remote terratec_ir_rc;
struct remote yamaha_ir_rc;
struct remote pollin_rf_rc;

#endif	/* REMOTE_H */
