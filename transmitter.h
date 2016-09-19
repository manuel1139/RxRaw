/* 
 * File:   transmitter.h
 * Author: manuel
 *
 * Created on 11. September 2016, 12:05
 */

#ifndef TRANSMITTER_H
#define	TRANSMITTER_H

void rf_tx_start();
void ir_tx_stop();

void ir_tx_start();

void TransmitISR();
void send_code(struct remote* r, uint16_t code);

#endif	/* TRANSMITTER_H */

