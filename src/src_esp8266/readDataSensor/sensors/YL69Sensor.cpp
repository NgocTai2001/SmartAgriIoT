#include "YL69Sensor.h"

YL69Sensor::YL69Sensor(int aPin, int dPin) {
  analogPin = aPin;
  digitalPin = dPin;

  if (digitalPin != -1) {
    pinMode(digitalPin, INPUT);
  }
}

int YL69Sensor::readAnalog() {
  return analogRead(analogPin);
}

bool YL69Sensor::readDigital() {
  if (digitalPin == -1) return false;
  return digitalRead(digitalPin) == LOW;
}

