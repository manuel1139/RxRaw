#include "timer.h"

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

/****************************************************************
 T0CON

76543210
1	timer on
 0      timer 16bit
  0     clock source -> internal clock
   x    surce edge sel
    1   prescaler bypass
     010  1:8 prescaler
 ******************************************************************/
void OpenTxTimer() {
    T0CON = 0b10000010;
    TMR0H = 0x0;
    TMR0L = 0x0;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
}

void WriteTxTimer(uint16_t val) {
    TMR0H = (val >> 8);
    TMR0L = val;
}

void CloseTxTimer() {
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 0;
}
