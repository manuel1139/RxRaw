
#include "capture.h"

/*********************************************************
 * 
 * OpenRxCapture  
 * 
 * 
 * 
CCP1CON
   76543210
   xx
     xx     //unsused in capture mode
       0000 >reest ccp module
       0100 >capt. every falling edge
       0101 capt. every rising edge

 ************************************************************/
#define CAP_EVERY_FALL_EDGE     0b00000100  	/* Capture on every falling edge*/
#define CAP_EVERY_RISE_EDGE     0b00000101  	/* Capture on every rising edge*/

void OpenRxCapture(uint8_t cfg) {
    CCP1CON = cfg & 0x0F;
    PIR1bits.CCP1IF = 0; // Clear the interrupt flag
    PIE1bits.CCP1IE = 1; // Enable the interrupt

    IPR1bits.CCP1IP = 1; //Timer 1 as source
}

uint16_t ReadRxCapture() {
    uint16_t val;
    val = CCPR1;
    return val;
}
#define StopRxCapture() CloseRxCapture()

void CloseRxCapture() {
    CCP1CON = 0x0;
}


