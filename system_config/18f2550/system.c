#include <xc.h>
#include "system.h"
#include "system_config.h"
#include "usb.h"
#include "usb_config.h"

void SYSTEM_Initialize(void)
{
 
    //todo: check 38khz/40khz PWM for IR-OUT 
    
    ADCON1 = 0x0f;  //All PORTABits DIGITAL
 
    /*******************************************************************/
    // Enable System Interupts
    /*******************************************************************/
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    RCONbits.IPEN = 1; //Interrupt priority
    
    IR_OUT_TRIS = OUTPUT_PIN;
        
    RF_OUT_TRIS = OUTPUT_PIN;

    LED1_TRIS = OUTPUT_PIN;
    LED2_TRIS = OUTPUT_PIN;
  
    DEAD_PIN_TRIS = INPUT_PIN;
    
    
}

