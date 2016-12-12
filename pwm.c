/*
 * PWM registers configuration
 * Fosc = 48000000 Hz
 * Fpwm = 37974.68 Hz (Requested : 38000 Hz)
 * Duty Cycle = 50 %
 * Resolution is 10 bits
 * Prescaler is 4*/

#include <xc.h>
#include <stdint.h>
#if defined(__18F2550)

void OpenPWM() {
    PR2 = 0b01001110;
    T2CON = 0b00000101;

    CCPR2L = 0b00100111;
    CCP2CON = 0b00010000;

}

void StartPWM() {
    CCP2CONbits.CCP2M = 0xC;
}

void StopPWM() {
    CCP2CONbits.CCP2M = 0;
}

void TogglePWM() {
    if (CCP2CONbits.CCP2M == 0xC) {
        CCP2CONbits.CCP2M = 0;
        LATBbits.LATB3 = 0;
    } else {
        CCP2CONbits.CCP2M = 0xC;
    }
}

void ClosePWM() {
    CCP2CONbits.CCP2M = 0;
}
#endif