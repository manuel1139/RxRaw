/* 
 * File:   receive_pulse_space.h
 * Author: manuel
 *
 * Created on 3. September 2016, 20:55
 */

#ifndef RECEIVE_PULSE_SPACE_H
#define	RECEIVE_PULSE_SPACE_H

struct remote;

void ir_rx(struct remote*, uint16_t);
void ir_pulse_space(struct remote*, uint16_t);

#endif	/* RECEIVE_PULSE_SPACE_H */

