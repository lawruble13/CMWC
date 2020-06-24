#define DEBUG 1
#define TESTING 0

#if DEBUG || TEST
#define _PP(a) Serial.print(a);
#define _PL(a) Serial.println(a);
#else
#define _PP(a) 
#define _PL(a) 
#endif

#include "CMWC_Instance.hpp"
#include <Arduino.h>

Scheduler ts;
#define N_INSTANCES 2
CMWC_Instance instances[N_INSTANCES];
CMWC_Status status = WAITING;
char currentlyFilling = -1;
bool timedOut[N_INSTANCES] = {false};

bool startWaiting();
void whileWaiting();
void endWaiting();

void checkWaterLevelWaiting();
char consecutiveEmpty[N_INSTANCES] = {0};

bool startFilling();
void whileFilling();
void endFilling();

Task waitingTask(CMWC_WAITING_CHECK_INTERVAL, TASK_FOREVER, &whileWaiting, &ts, true, &startWaiting, &endWaiting);
Task fillingTask(CMWC_FILLING_CHECK_INTERVAL, CMWC_FILLING_TIMEOUT / CMWC_FILLING_CHECK_INTERVAL, &whileFilling, &ts, false, &startFilling, &endFilling);
Task waitingCheckLevelTask(TASK_IMMEDIATE, N_INSTANCES, &checkWaterLevelWaiting, &ts, false);

void setup() {
#if DEBUG || TEST
  Serial.begin(115200);
#endif

//  instances[0].setPins(7,11,10,A0);
  instances[1].setPins(8,12,9,A1);

  instances[0].init();
  instances[1].init();
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  static bool init = false;
  if(!init){
    _PL("Starting CMWC Version 0.1");
    init = true;
  }
  ts.execute();
}

bool startWaiting(){
  // Perform checks before starting waiting
  _PL("Starting wait task.");
  return true;
}

void whileWaiting(){
  for(int i = 0; i < N_INSTANCES; i++){
    if(instances[i].isConnected())
      instances[i].enableSensor();
  }
  waitingCheckLevelTask.restartDelayed(CMWC_DELAY_CHECK);
  _PL("Enabled all sensors, checking values after delay.");
}

void endWaiting(){
  for(int i = 0; i < N_INSTANCES; i++){
    if(i == currentlyFilling) continue;
    instances[i].disableSensor();
  }
  _PL("Ending wait task, disabled all non-filling sensors.");
}


void checkWaterLevelWaiting(){
  static char currentlyChecking = -1;
  currentlyChecking = (currentlyChecking+1) % N_INSTANCES;
  _PP("Checking level of instance");
  _PL(String(currentlyChecking));
  if(timedOut[currentlyChecking]){
    _PL("This instance timed out. Continuing.");
    return;
  }
  if(!instances[currentlyChecking].isConnected()){
    _PL("This instance isn't connected. Continuing.");
    return;
  }
  if(instances[currentlyChecking].getWaterLevel() < CMWC_DETECT_LEVEL){
    _PP("Measured empty. Consecutive empties: ");
    _PL(String(consecutiveEmpty[currentlyChecking]+1));
    if(++consecutiveEmpty[currentlyChecking] >= CMWC_WAITING_CONSEC_EMPTY){
      currentlyFilling = currentlyChecking;
      waitingTask.disable();
      waitingCheckLevelTask.disable();
      fillingTask.restart();
      consecutiveEmpty[currentlyChecking] = 0;
    } else {
      instances[currentlyChecking].disableSensor();
    }
  } else {
    _PL("Measured not empty");
    consecutiveEmpty[currentlyChecking] = 0;
    instances[currentlyChecking].disableSensor();
  }
}


bool startFilling(){
  instances[currentlyFilling].enableValve();
  _PL("Starting fill task");
  return true;
}

void whileFilling(){
  int level = instances[currentlyFilling].getWaterLevel();
  _PP("Measured level while filling: ");
  _PL(level);
  if(level > CMWC_DETECT_LEVEL){
    fillingTask.disable();
    waitingTask.enable();
  }
}

void endFilling(){
  if(fillingTask.getIterations() == 0){
    timedOut[currentlyFilling] = true;
    _PL("Fill timed out.");
  }
  instances[currentlyFilling].disableValve();
  instances[currentlyFilling].disableSensor();
  _PL("Ending fill task");
}
