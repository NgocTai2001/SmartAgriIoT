#include "LM393LDRSensor.h"

LM393LDRSensor::LM393LDRSensor(int aPin, int dPin) {
  analogPin = aPin;
  digitalPin = dPin;

  if (digitalPin != -1) {
    pinMode(digitalPin, INPUT);
  }
}

int LM393LDRSensor::readLightAnalog() {
  int raw = analogRead(analogPin); // 0–4095 trên ESP32
  int percent = map(4095 - raw, 0, 4095, 0, 100);

  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;

  return percent;
}

bool LM393LDRSensor::readLightDigital() {
  if (digitalPin == -1) return false;
  return digitalRead(digitalPin) == LOW;
}