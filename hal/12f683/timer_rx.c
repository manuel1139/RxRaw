#include "timer_rx.h"

/**************************************************************
 T1CON
 * 
 * 
 * 
 ****************************************************************/
void OpenRxTimer() {
    T1CON = 0b00000001;
    TMR1H = 0;
    TMR1L = 0;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;

}

uint16_t ReadRxTimer() {
    uint16_t val = 0;
    val = TMR1H << 8;
    val |= TMR1L;
    return val;
}

void WriteRxTimer(uint16_t val) {
    TMR1H = val >> 8;
    TMR1L = val;
}

