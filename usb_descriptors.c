
/*********************************************************************
 * Descriptor specific type definitions are defined in:
 * usb_device.h
 *
 * Configuration options are defined in:
 * usb_config.h
 ********************************************************************/
#ifndef __USB_DESCRIPTORS_C
#define __USB_DESCRIPTORS_C

/** INCLUDES *******************************************************/
#include "usb.h"
#include "usb_device_hid.h"

/** CONSTANTS ******************************************************/

/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR device_dsc ={
    0x12, // Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE, // DEVICE descriptor type
    0x0200, // USB Spec Release Number in BCD format
    0x00, // Class Code
    0x00, // Subclass code
    0x00, // Protocol code
    USB_EP0_BUFF_SIZE, // Max packet size for EP0, see usb_config.h
    0x04D8, // Vendor ID
    0x003F, // Product ID: Custom HID device demo
    0x0100, // Device release number in BCD format
    0x01, // Manufacturer string index
    0x02, // Product string index
    0x00, // Device serial number string index
    0x01 // Number of possible configurations
};

/* Configuration 1 Descriptor */
const uint8_t configDescriptor1[] = {
    /* Configuration Descriptor */
    0x09, //sizeof(USB_CFG_DSC),    // Size of this descriptor in bytes
    USB_DESCRIPTOR_CONFIGURATION, // CONFIGURATION descriptor type
    0x29, 0x00, // Total length of data for this cfg
    1, // Number of interfaces in this cfg
    1, // Index value of this configuration
    0, // Configuration string index
    _DEFAULT | _SELF, // Attributes, see usb_device.h
    50, // Max power consumption (2X mA)

    /* Interface Descriptor */
    0x09, //sizeof(USB_INTF_DSC),   // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE, // INTERFACE descriptor type
    0, // Interface Number
    0, // Alternate Setting Number
    2, // Number of endpoints in this intf
    HID_INTF, // Class code
    0, // Subclass code
    0, // Protocol code
    0, // Interface string index

    /* HID Class-Specific Descriptor */
    0x09, //sizeof(USB_HID_DSC)+3,    // Size of this descriptor in bytes
    DSC_HID, // HID descriptor type
    0x11, 0x01, // HID Spec Release Number in BCD format (1.11)
    0x00, // Country Code (0x00 for Not supported)
    HID_NUM_OF_DSC, // Number of class descriptors, see usbcfg.h
    DSC_RPT, // Report descriptor type
    HID_RPT01_SIZE, 0x00, //sizeof(hid_rpt01),      // Size of the report descriptor

    /* Endpoint Descriptor */
    0x07, /*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT, //Endpoint Descriptor
    CUSTOM_DEVICE_HID_EP | _EP_IN, //EndpointAddress
    _INTERRUPT, //Attributes
    0x40, 0x00, //size
    0x01, //Interval

    /* Endpoint Descriptor */
    0x07, /*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT, //Endpoint Descriptor
    CUSTOM_DEVICE_HID_EP | _EP_OUT, //EndpointAddress
    _INTERRUPT, //Attributes
    0x40, 0x00, //size
    0x01 //Interval
};

//Language code string descriptor

const struct {
    uint8_t bLength;
    uint8_t bDscType;
    uint16_t string[1];
}
sd000 = {
    sizeof (sd000), USB_DESCRIPTOR_STRING, {
        0x0409}
};

//Manufacturer string descriptor

const struct {
    uint8_t bLength;
    uint8_t bDscType;
    uint16_t string[25];
}
sd001 = {
    sizeof (sd001), USB_DESCRIPTOR_STRING, {
        'M', 'i', 'c', 'r', 'o', 'c', 'h', 'i', 'p', ' ',
        'T', 'e', 'c', 'h', 'n', 'o', 'l', 'o', 'g', 'y', ' ', 'I', 'n', 'c', '.'}
};

//Product string descriptor

const struct {
    uint8_t bLength;
    uint8_t bDscType;
    uint16_t string[22];
}
sd002 = {
    sizeof (sd002), USB_DESCRIPTOR_STRING, {
        'S', 'i', 'm', 'p', 'l', 'e', ' ', 'H', 'I', 'D', ' ',
        'D', 'e', 'v', 'i', 'c', 'e', ' ', 'D', 'e', 'm', 'o'}
};

//Class specific descriptor - HID 

const struct {
    uint8_t report[HID_RPT01_SIZE];
} hid_rpt01 = {
    {
   		0x06, 0x00, 0xff, 	// USAGE_PAGE (Vendor Defined Page 1)
		0x09, 0x01,       	// USAGE (Vendor Usage 1)
		0xa1, 0x01,       	// COLLECTION (Application)

		// The Input report
		0x09, 0x00,     	// Usage ID - vendor defined
		0x15, 0x00,     	// Logical Minimum (0)
		0x26, 0xFF, 0x00, 	// Logical Maximum (255)
		0x75, 0x20,     	// Report Size (8 bits)
		0x95, 0x8,     	// Report Count (64 fields)
		0x81, 0x02,     	// Input (Data, Variable, Absolute)

		// The Output report
		0x09, 0x04,     	// Usage ID - vendor defined
		0x15, 0x00,     	// Logical Minimum (0)
		0x26, 0xFF, 0x00, 	// Logical Maximum (255)
		0x75, 0x08,     	// Report Size (8 bits)
		0x95, 0x40,     	// Report Count (64 fields)
		0x91, 0x02,      	// Output (Data, Variable, Absolute)

		// The Feature report
		0x09, 0x01,     	// Usage ID - vendor defined
		0x15, 0x00,     	// Logical Minimum (0)
		0x26, 0xFF, 0x00, 	// Logical Maximum (255)
		0x75, 0x08,     	// Report Size (8 bits)
		0x95, 0x40,     	// Report Count (64 fields)
		0xB1, 0x02,      	// Feature (Data, Variable, Absolute)

		0xc0              	// END_COLLECTION
    } // End Collection
};


//Array of configuration descriptors
const uint8_t * const USB_CD_Ptr[] ={
    (const uint8_t * const) &configDescriptor1
};

//Array of string descriptors
const uint8_t * const USB_SD_Ptr[] ={
    (const uint8_t * const) &sd000,
    (const uint8_t * const) &sd001,
    (const uint8_t * const) &sd002
};

/** EOF usb_descriptors.c ***************************************************/

#endif
