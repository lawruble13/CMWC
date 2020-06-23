#define DEBUG_MODE

#include <TaskScheduler.h>
#include "CMWC_Instance.h"

Scheduler ts;
CMWC_Instance g_cmwc_inst1;
//CMWC_Instance g_cmwc_inst2;

void setup() {
  ts.init();
  g_cmwc_inst1.init();
  
}

void loop() {
  
}
