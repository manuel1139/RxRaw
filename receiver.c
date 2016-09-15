#include <xc.h>
#include <stdlib.h>

#include "receiver.h"
#include "capture.h"
#include "timer.h"
#include "receive_raw.h"


#include "remote.h"

/*
const remote *Remotes[] = {
        &terratec_ir_rc,
        &yamaha_ir_rc,
        0
    };
 */

void ReceiveISR() {
    if (PIR1bits.CCP1IF) {
        //inverts edge detection 
        CCP1CONbits.CCP1M0 = ~CCP1CONbits.CCP1M0; //invert edge detection
 
        //CCPR1H = TMR1H;  //debug only
        uint16_t cval = ReadRxCapture();
        rx_raw(cval);
        //struct  remote *r;
        //for (r; r != 0; r++); // r->pRcvFunc(r, cval);
        //        terratec_ir_rc.rx_func(&terratec_ir_rc, cval);
        //        yamaha_ir_rc.rx_func(&yamaha_ir_rc, cval);
        minfiniy_led.rx_func(&minfiniy_led, cval);
        WriteRxTimer(0);
        PIR1bits.CCP1IF = 0;
    }

    if (PIR1bits.TMR1IF) {
        rx_raw_timeo();
        for (int i = 0; remotes[i]; i++) {
            remotes[i]->init_rx(remotes[i]);
        }
        CCP1CONbits.CCP1M0 = 0; //capture every falling edge
        PIR1bits.TMR1IF = 0;
    }
}

void ir_rx_start() {

    CCPR1 = 0; //Timer data register zero (word)

    if (PORTCbits.RC2 == 1) {
        OpenRxCapture(CAP_EVERY_FALL_EDGE);
    } else {
        OpenRxCapture(CAP_EVERY_RISE_EDGE);
    }
    OpenRxTimer();
}

void ir_rx_stop() {
    CloseRxCapture();
}

