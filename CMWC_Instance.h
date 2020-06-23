#ifdef CMWC_INSTANCE_H
#define CMWC_INSTANCE_H

#include <TaskScheduler.h>

#define CMWC_INSTANCE_SENSOR_POWER_ON_WAIT (10 * TASK_MILLISECOND)

#ifdef DEBUG_MODE

#define CMWC_TIME_BETWEEN_CHECKS (1 * TASK_SECOND)
#define CMWC_FILL_MAX_TIMEOUT (1 * TASK_SECOND)

#else

#define CMWC_TIME_BETWEEN_CHECKS (1 * TASK_MINUTE)
#define CMWC_FILL_MAX_TIMEOUT (1 * TASK_MINUTE)

#endif // DEBUG_MODE

class CMWC_Instance {
  private:
  int m_senPowPin_n;
  int m_valPowPin;
  int m_devConPin;
  int m_senARdPin;

  bool m_senEnabled;
  bool m_valEnabled;

  public:
  CMWC_Instance(int p_senPowPin_n=7, int p_valPowPin=11, int p_devConPin=10, int p_senArdPin=A0);
  void init();

  int getWaterLevel();
  void enableSensor();
  void disableSensor();

  void enableValve();
  void disableValve();

  bool isConnected();
}

#endif // CMWC_INSTANCE_H
