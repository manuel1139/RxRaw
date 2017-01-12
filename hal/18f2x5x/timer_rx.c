#include "timer_rx.h"

/**************************************************************
 T1CON

76543210
1	  16 bit rw
 0	  T1RUN t1 run in osc mode (read only)
  11      1:8 prescaler
    0     Timer1 osc off
     0
      0    Internal clock	 
       1   Enable Timer 
 
 ****************************************************************/
void OpenRxTimer() {
    T1CON = 0b10110001;
    TMR1H = 0;
    TMR1L = 0;
    T3CONbits.T3CCP2 = 0;
    T3CONbits.T3CCP1 = 0;
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

