#include "CMWC_Instance.hpp"
#include <Arduino.h>

#define DEBUG 1

Scheduler ts;
CMWC_Instance g_cmwc_inst1(7, 11, 10, A0);

void blinkTaskCallback();

Task blinkTask(1*TASK_SECOND, TASK_FOREVER, &blinkTaskCallback, &ts);

void setup() {

  g_cmwc_inst1.init();
  pinMode(LED_BUILTIN, OUTPUT);

#if DEBUG
  Serial.begin(115200);
  Serial.println("Beginning serial debug.");
#endif

  blinkTask.enable();
}

void loop() {
  ts.execute();
}

void blinkTaskCallback(){
  static bool on = false;
  if (on){
    digitalWrite(LED_BUILTIN, LOW);
    g_cmwc_inst1.enableSensor();
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    g_cmwc_inst1.disableSensor();
  }
  on = !on;
}
