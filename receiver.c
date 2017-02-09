#include <xc.h>
#include <stdlib.h>

#include "receiver.h"
#include "capture.h"
#include "timer_rx.h"
#include "receive_raw.h"

#include "remote.h"
#include "system.h"


extern struct remote * remotes[];

void ReceiveISR() {
    if (PIR1bits.CCP1IF) {
        //inverts edge detection 
        //        PIE1bits.CCP1IE = 0;
        CCP1CONbits.CCP1M0 = CCP1CONbits.CCP1M0 ^ 1;

        uint16_t cval = ReadRxCapture();
        //ticks to millis
        cval = cval * 2 / 3;
        rx_raw(cval); //todo:

        for (int i = 0; remotes[i]; i++) {
            remotes[i]->rx_func(remotes[i], cval);
        }

        WriteRxTimer(0);
        //        PIE1bits.CCP1IE = 1;
        PIR1bits.CCP1IF = 0;
    }

    if (PIR1bits.TMR1IF) {
        rx_raw_timeo();
        //rx timeout();
        for (int i = 0; remotes[i]; i++) {
        //    if (!remotes[i]->rx_data.code_found)
                remotes[i]->init_rx(remotes[i]);
        //    else {
        //        uint16_t c = remotes[i]->rx_data.code_found;
        //    }
        }
        //reseet to active high/low depending on receiver
        //state after timeout 
        CCP1CON = 0; //
        IR_RCV ? CCP1CON = 0b100 : CCP1CON = 0b101;
        PIR1bits.TMR1IF = 0;
//        LED2=0;
    }
}

void ir_rx_start() {

    CCPR1 = 0; //Timer data register zero (word)

    if (IR_RCV == 1) {
        OpenRxCapture(CAP_EVERY_FALL_EDGE);
    } else {
        OpenRxCapture(CAP_EVERY_RISE_EDGE);
    }
    OpenRxTimer();
}

void ir_rx_stop() {
    CloseRxCapture();
}

