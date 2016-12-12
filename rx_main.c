
#include <xc.h>
#include <stdbool.h>       /* For true/false definition */
#include <stdint.h>        /* For uint8_t definition */

#include "system.h"

#include "receiver.h"
#include "remote.h"
#include "capture.h"

extern struct remote minfiniy_led;

struct remote* remotes[] = {
    &minfiniy_led,
    0
};

int main(void) {
    SYSTEM_Initialize();
    for (int i = 0; remotes[i]; i++) {
        remotes[i]->init_rx(remotes[i]);
    }
    ir_rx_start();
    while(1);
}

void high_priority interrupt high_isr(void) {
    ReceiveISR();
}


