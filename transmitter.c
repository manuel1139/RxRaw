
#include <xc.h>
#include <stdlib.h>
#include <stdint.h>

#include "system.h"

#include "receiver.h"
#include "receive_raw.h"

#include "capture.h"
#include "timer_tx.h"
#include "pwm.h"

#include "remote.h"


volatile uint8_t transmitter_state = 0;

void rf_tx_start() {
    OpenTxTimer();
    RF_OUT = 0;

}

void ir_tx_stop() {
    CloseTxTimer();
}

#if defined(__18F2550)

void ir_tx_start() {
    OpenPWM();
}
#endif

void send_code(struct remote* r, uint16_t code) {
    if (transmitter_state == 0) {
        transmitter_state = 1;
        r->tx_data.code_to_send = code;
        INTCONbits.TMR0IF = 1;
    }
}

void TransmitISR() {
    if (INTCONbits.TMR0IF) {
        for (int i = 0; remotes[i]; i++) {
            if (remotes[i]->tx_data.code_to_send != 0)
                remotes[i]->tx_func(remotes[i]);
        }
        INTCONbits.TMR0IF = 0;
    }
}