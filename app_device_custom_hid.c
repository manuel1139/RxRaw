#include "usb.h"
#include "usb_device_hid.h"

#include <string.h>

#include "system.h"

#include "remote.h"

/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
#if defined(COMPILER_MPLAB_C18)
#pragma udata HID_CUSTOM_OUT_DATA_BUFFER = HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS
unsigned char ReceivedDataBuffer[64];
#pragma udata HID_CUSTOM_IN_DATA_BUFFER = HID_CUSTOM_IN_DATA_BUFFER_ADDRESS
unsigned char ToSendDataBuffer[64];
#pragma udata

#else defined(__XC8)
unsigned char ReceivedDataBuffer[64] @ HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS;
unsigned char ToSendDataBuffer[64] @ HID_CUSTOM_IN_DATA_BUFFER_ADDRESS;
#endif
#else
unsigned char ReceivedDataBuffer[64];
unsigned char ToSendDataBuffer[64];
#endif

volatile USB_HANDLE USBOutHandle;
volatile USB_HANDLE USBInHandle;

/** DEFINITIONS ****************************************************/
typedef enum {
    COMMAND_TOGGLE_LED = 0x80,
    COMMAND_GET_BUTTON_STATUS = 0x81,
    COMMAND_READ_POTENTIOMETER = 0x37
} CUSTOM_HID_DEMO_COMMANDS;

/** FUNCTIONS ******************************************************/

/*********************************************************************
 * Function: void APP_DeviceCustomHIDInitialize(void);
 *
 * Overview: Initializes the Custom HID demo code
 *
 * PreCondition: None
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
void APP_DeviceCustomHIDInitialize() {
    //initialize the variable holding the handle for the last
    // transmission
    USBInHandle = 0;

    //enable the HID endpoint
    USBEnableEndpoint(CUSTOM_DEVICE_HID_EP, USB_IN_ENABLED | USB_OUT_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);

    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = (volatile USB_HANDLE)HIDRxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*) & ReceivedDataBuffer, 64);
}

/*********************************************************************
 * Function: void APP_DeviceCustomHIDTasks(void);
 *
 * Overview: Keeps the Custom HID demo running.
 *
 * PreCondition: The demo should have been initialized and started via
 *   the APP_DeviceCustomHIDInitialize() and APP_DeviceCustomHIDStart() demos
 *   respectively.
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
void APP_DeviceCustomHIDTasks() {
    //todo: usb_remotes!
    extern struct remote * remotes[];
    for (int i = 0; remotes[i]; i++) {
        if (remotes[i]->rx_data.code_found != 0) {
            if (!HIDTxHandleBusy(USBInHandle)) {
                LED1 = 1;
                ToSendDataBuffer[7] = 0;
                ToSendDataBuffer[6] = 0;
                ToSendDataBuffer[5] = (uint8_t) remotes[i]->rx_data.code_found;
                ToSendDataBuffer[4] = remotes[i]->rx_data.code_found >> 8;

                ToSendDataBuffer[3] = 0;
                ToSendDataBuffer[2] = 0;
                ToSendDataBuffer[1] = (uint8_t) remotes[i]->rx_data.code_found;
                ToSendDataBuffer[0] = remotes[i]->rx_data.code_found >> 8;

                USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*) & ToSendDataBuffer[0], 32);
                remotes[i]->rx_data.code_found = 0;
                LED1 = 0;
            }
        }
    }
}
