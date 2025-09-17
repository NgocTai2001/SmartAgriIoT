#include "AnemometerSensor.h"

AnemometerSensor::AnemometerSensor(int inputPin, float factor) {
  pin = inputPin;
  pulseCount = 0;
  lastTime = 0;
  calibrationFactor = factor;
}

void AnemometerSensor::begin() {
  pinMode(pin, INPUT_PULLUP);
  attachInterruptArg(digitalPinToInterrupt(pin), handleInterruptWrapper, this, FALLING);
}

void IRAM_ATTR AnemometerSensor::handleInterruptWrapper(void* arg) {
  AnemometerSensor* sensor = static_cast<AnemometerSensor*>(arg);
  sensor->handleInterrupt();
}

void AnemometerSensor::handleInterrupt() {
  pulseCount++;
}

float AnemometerSensor::readWindSpeed() {
  unsigned long currentTime = millis();
  unsigned long elapsed = currentTime - lastTime;

  if (elapsed < 1000) return -1; // wait at least 1s for a stable reading

  float frequency = (pulseCount * 1000.0) / elapsed;
  float windSpeed = frequency / calibrationFactor;

  lastTime = currentTime;
  pulseCount = 0;

  return windSpeed;
}

void AnemometerSensor::reset() {
  pulseCount = 0;
  lastTime = millis();
}