#include <TaskSchedulerDeclarations.h>

#ifndef CMWC_INSTANCE_H
#define CMWC_INSTANCE_H

#define mytest (1*TASK_SECOND)

class CMWC_Instance {
  private:
  int m_senPowPin_n;
  int m_valPowPin;
  int m_devConPin;
  int m_senARdPin;

  bool m_senEnabled;
  bool m_valEnabled;

  public:
  CMWC_Instance(int p_senPowPin_n, int p_valPowPin, int p_devConPin, int p_senARdPin);
  void init();

  int getWaterLevel();
  void enableSensor();
  void disableSensor();

  void enableValve();
  void disableValve();

  bool isConnected();
};

#endif // CMWC_INSTANCE_H
