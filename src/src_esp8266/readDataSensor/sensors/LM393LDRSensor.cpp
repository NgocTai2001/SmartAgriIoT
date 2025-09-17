#include "LM393LDRSensor.h"

LM393LDRSensor::LM393LDRSensor(int aPin, int dPin) {
  analogPin = aPin;
  digitalPin = dPin;

  if (digitalPin != -1) {
    pinMode(digitalPin, INPUT);
  }
}

int LM393LDRSensor::readLightAnalog() {
  return analogRead(analogPin);
}

bool LM393LDRSensor::readLightDigital() {
  if (digitalPin == -1) return false;
  return digitalRead(digitalPin) == LOW;
}