
#include <xc.h>
#include <stdlib.h>

#include "receiver.h"
#include "capture.h"
#include "timer.h"
#include "receive_raw.h"


#include "remote.h"

void rf_tx_start() {
    OpenTxTimer();
    
}

void ir_tx_stop() {
    CloseTxTimer();
}
