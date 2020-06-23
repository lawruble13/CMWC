#include <TaskScheduler.h>
#include "CMWC_Instance.h"

public CMWC_Instance::CMWC_Instance(int p_senPowPin_n=7, int p_valPowPin=11, int p_devConPin=10, int p_senArdPin=A0){
  m_senPowPin_n = p_senPowPin_n;
  m_valPowPin   = p_valPowPin;
  m_devConPin   = p_devConPin;
  m_senARdPin   = p_senARdPin;
}
public void CMWC_Instance::init(){
  pinMode(m_senPowPin_n, OUTPUT);
  digitalWrite(m_senPowPin_n, HIGH);
  m_senEnabled = false;
  
  pinMode(m_valPowPin, OUTPUT);
  digitalWrite(m_valPowPin, LOW);
  m_valEnabled = false;
  
  pinMode(m_devConPin, INPUT);
  pinMode(m_senARdPin, INPUT);
}

public int CMWC_Instance::getWaterLevel(){
  if(m_senEnabled){
    return analogRead(m_senARdPin);
  } else {
    return -1;
  }
}
public void CMWC_Instance::enableSensor(){
  digitalWrite(m_senPowPin_n, LOW);
  m_senEnabled = true;
}
public void CMWC_Instance::disableSensor(){
  digitalWrite(m_senPowPin_n, HIGH);
  m_senEnabled = false;
}

public void CMWC_Instance::enableValve(){
  digitalWrite(m_valPowPin, HIGH);
  m_valEnabled = true;
}
public void CMWC_Instance::disableValve(){
  digitalWrite(m_valPowPin, LOW);
  m_valEnabled = false;
}

public bool CMWC_Instance::isConnected(){
  return (digitalRead(m_devConPin) == LOW);
}
