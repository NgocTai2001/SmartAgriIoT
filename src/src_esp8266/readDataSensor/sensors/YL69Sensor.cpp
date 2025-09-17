#include "YL69Sensor.h"

YL69Sensor::YL69Sensor(int aPin, int dPin) {
  analogPin = aPin;
  digitalPin = dPin;

  if (digitalPin != -1) {
    pinMode(digitalPin, INPUT);
  }
}

int YL69Sensor::readSoilAnalog() {
  return analogRead(analogPin);
}

bool YL69Sensor::readSoilDigital() {
  if (digitalPin == -1) return false;
  return digitalRead(digitalPin) == LOW;
}

