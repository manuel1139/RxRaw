/* 
 * File:   timer.h
 * Author: manuel
 *
 * Created on 1. September 2016, 10:08
 */

#include <xc.h>
#include <stdint.h>

#ifndef TIMER_RX_H
#define	TIMER_RX_H

void OpenRxTimer();
uint16_t ReadRxTimer();
void WriteRxTimer(uint16_t val);

#endif	/* TIMER_H */

