/* 
 * File:   pwm.h
 * Author: manuel
 *
 * Created on 16. September 2016, 15:02
 */

#ifndef PWM_H
#define	PWM_H


#include <xc.h>
#include <stdint.h>

void OpenPWM();
void ClosePWM();
void StartPWM();
void StopPWM();
void TogglePWM();


#endif	/* PWM_H */

