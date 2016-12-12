/* 
 * File:   timer.h
 * Author: manuel
 *
 * Created on 1. September 2016, 10:08
 */

#include <xc.h>
#include <stdint.h>

#ifndef TIMER_TX_H
#define	TIMER_TX_H

void OpenTxTimer();
void WriteTxTimer(uint16_t val);
void CloseTxTimer();

#endif	/* TIMER_H */

