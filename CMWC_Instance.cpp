#include <Arduino.h>
#include "CMWC_Instance.hpp"

CMWC_Instance::CMWC_Instance(int p_senPowPin_n, int p_valPowPin, int p_devConPin, int p_senARdPin){
  m_senPowPin_n = p_senPowPin_n;
  m_valPowPin   = p_valPowPin;
  m_devConPin   = p_devConPin;
  m_senARdPin   = p_senARdPin;
}

void CMWC_Instance::init(){
  pinMode(m_senPowPin_n, OUTPUT);
  digitalWrite(m_senPowPin_n, HIGH);
  m_senEnabled = false;
  
  pinMode(m_valPowPin, OUTPUT);
  digitalWrite(m_valPowPin, LOW);
  m_valEnabled = false;
  
  pinMode(m_devConPin, INPUT);
  pinMode(m_senARdPin, INPUT);
}

int CMWC_Instance::getWaterLevel(){
  if(m_senEnabled){
    return analogRead(m_senARdPin);
  } else {
    return -1;
  }
}
void CMWC_Instance::enableSensor(){
  digitalWrite(m_senPowPin_n, LOW);
  m_senEnabled = true;
}
void CMWC_Instance::disableSensor(){
  digitalWrite(m_senPowPin_n, HIGH);
  m_senEnabled = false;
}

void CMWC_Instance::enableValve(){
  digitalWrite(m_valPowPin, HIGH);
  m_valEnabled = true;
}
void CMWC_Instance::disableValve(){
  digitalWrite(m_valPowPin, LOW);
  m_valEnabled = false;
}

bool CMWC_Instance::isConnected(){
  return (digitalRead(m_devConPin) == LOW);
}
