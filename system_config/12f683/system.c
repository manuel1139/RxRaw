#include <xc.h>
#include "system.h"
#include "system_config.h"

void SYSTEM_Initialize(void)
{
    /*******************************************************************/
    // Enable System Interupts
    /*******************************************************************/
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}


