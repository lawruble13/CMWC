#include <TaskSchedulerDeclarations.h>
#include <Arduino.h>

#ifndef CMWC_INSTANCE_H
#define CMWC_INSTANCE_H

#if DEBUG
#define CMWC_WAITING_CHECK_INTERVAL (1*TASK_SECOND)
#define CMWC_WAITING_CONSEC_EMPTY 5
#define CMWC_FILLING_CHECK_INTERVAL (100*TASK_MILLISECOND)
#define CMWC_FILLING_TIMEOUT (1*TASK_MINUTE)
#else
#define CMWC_WAITING_CHECK_INTERVAL (1*TASK_MINUTE)
#define CMWC_WAITING_CONSEC_EMPTY 10
#define CMWC_FILLING_CHECK_INTERVAL (100*TASK_MILLISECOND)
#define CMWC_FILLING_TIMEOUT (1*TASK_MINUTE)
#endif

#define CMWC_DELAY_CHECK (10*TASK_MILLISECOND)
#define CMWC_DETECT_LEVEL 100

class CMWC_Instance {
  private:
  int m_senPowPin_n;
  int m_valPowPin;
  int m_devConPin;
  int m_senARdPin;

  bool m_senEnabled;
  bool m_valEnabled;

  public:
  CMWC_Instance(int p_senPowPin_n=7, int p_valPowPin=11, int p_devConPin=10, int p_senARdPin=A0);
  void setPins(int p_senPowPin_n=7, int p_valPowPin=11, int p_devConPin=10, int p_senARdPin=A0);
  void init();

  int getWaterLevel();
  void enableSensor();
  void disableSensor();

  void enableValve();
  void disableValve();

  bool isConnected();
  bool isSensorEnabled();
  bool isValveEnabled();
};

enum CMWC_Status { WAITING, FILLING };

#endif // CMWC_INSTANCE_H
