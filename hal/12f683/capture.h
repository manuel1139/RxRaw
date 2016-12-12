/* 
 * File:   capture.h
 * Author: manuel
 *
 * Created on 1. September 2016, 10:15
 */
#include <xc.h>
#include <stdint.h>

#ifndef CAPTURE_H
#define	CAPTURE_H

#define CAP_EVERY_FALL_EDGE     0b00000100  	/* Capture on every falling edge*/
#define CAP_EVERY_RISE_EDGE     0b00000101  	/* Capture on every rising edge*/

void OpenRxCapture(uint8_t cfg);
uint16_t ReadRxCapture();
void CloseRxCapture();

#endif	/* CAPTURE_H */

