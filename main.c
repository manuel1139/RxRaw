#include <xc.h>
#include <stdbool.h>       /* For true/false definition */
#include <stdint.h>        /* For uint8_t definition */

#include "system.h"

#include "usb.h"
#include "usb_device_hid.h"

#include "app_device_custom_hid.h"

#include "receiver.h"
#include "transmitter.h"
#include "remote.h"

/*
void putch(unsigned char data) {
    while (!PIR1bits.TXIF) // wait until the transmitter is ready
        continue;
    TXREG = data; // send one character
}

void init_uart(void) {
    TXSTAbits.TXEN = 1; // enable transmitter
    RCSTAbits.SPEN = 1; // enable serial port
}
 */

int main(void) {

    //init_uart();
    //rintf("starting\n");
    SYSTEM_Initialize();

    USBDeviceInit();
    USBDeviceAttach();

    for (int i=0; remotes[i]; i++) {
        remotes[i]->init(remotes[i]);
    }

    ir_rx_start();
    rf_tx_start();
    /*
    typedef struct {
        const char *name;
        const uint8_t type;
        const uint8_t val;
    } stateful_dev;

    typedef struct{
        char *remote;
    
    };

    stateful_dev sfd = { "Wohnzimmer Licht", 0, 0 };
    commands cmd = =
    //remote* r, code, command
     */
send_code(&pollin_rf_rc, STEST);

    while (1) {

        if (minfiniy_led.rx_data.code_found == minfiniy_led.keys[0]) {
            send_code(&pollin_rf_rc, S2_ON);
            send_code(&pollin_rf_rc, S2_ON);
            send_code(&pollin_rf_rc, S2_ON);

            minfiniy_led.rx_data.code_found = 0;
        }
        if (minfiniy_led.rx_data.code_found == minfiniy_led.keys[1]) {
            send_code(&pollin_rf_rc, S2_OFF);
            send_code(&pollin_rf_rc, S2_OFF);
            send_code(&pollin_rf_rc, S2_OFF);

            minfiniy_led.rx_data.code_found = 0;

        }




        //Non USB tasks
        //LED1 = ~IR_RCV;
        //LED2 = RF_OUT;

        if (USBGetDeviceState() < CONFIGURED_STATE) {
            /* Jump back to the top of the while loop. */
            continue;
        }

        if (USBIsDeviceSuspended() == true) {
            /* Jump back to the top of the while loop. */
            continue;
        }
        //Application specific tasks
        APP_DeviceCustomHIDTasks();

    }
}

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size) {
    switch ((int) event) {
        case EVENT_TRANSFER:
            break;

        case EVENT_SOF:
            /* We are using the SOF as a timer to time the LED indicator.  Call
             * the LED update function here. */
            //            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_SUSPEND:
            /* Update the LED status for the suspend event. */
            //            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_RESUME:
            /* Update the LED status for the resume event. */
            //            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_CONFIGURED:
            /* When the device is configured, we can (re)initialize the demo
             * code. */
            APP_DeviceCustomHIDInitialize();
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The HID driver
             * needs to check to see if the request was for it. */
            USBCheckHIDRequest();
            break;

        case EVENT_BUS_ERROR:
            break;

        case EVENT_TRANSFER_TERMINATED:
            break;

        default:
            break;
    }
    return true;
}

void high_priority interrupt high_isr(void) {

    USBDeviceTasks();

    ReceiveISR();

    TransmitISR();

}

