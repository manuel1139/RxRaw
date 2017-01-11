#include "timer_tx.h"

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
