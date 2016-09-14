
#include <xc.h>
#include <stdlib.h>
#include <stdint.h>

#include "receiver.h"
#include "capture.h"
#include "timer.h"
#include "receive_raw.h"
#include "system.h"
#include "remote.h"

void rf_tx_start() {
    OpenTxTimer();
    RF_OUT = 0;
    
}

void ir_tx_stop() {
    CloseTxTimer();
}

void send_code(struct remote* r, uint16_t code) {
    r->tx_data.code_to_send = code;
    INTCONbits.TMR0IF = 1;
}
void TransmitISR() {
     if (INTCONbits.TMR0IF) {
         if (pollin_rf_rc.tx_data.code_to_send != 0)
            pollin_rf_rc.tx_func(&pollin_rf_rc);
        INTCONbits.TMR0IF = 0;
    }
 }