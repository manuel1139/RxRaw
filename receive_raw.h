/* 
 * File:   receive_raw.h
 * Author: manuel
 *
 * Created on 31. August 2016, 20:59
 */

#ifndef RECEIVE_RAW_H
#define	RECEIVE_RAW_H

#include <xc.h>
#include <stdint.h>

void rx_raw(uint16_t bit_time);
void rx_raw_timeo();

#endif	/* RECEIVE_RAW_H */

