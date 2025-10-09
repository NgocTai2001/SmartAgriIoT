#include "AnemometerSensor.h"

AnemometerSensor::AnemometerSensor(int analogPin, float factor) {
  pin = analogPin;
  calibrationFactor = factor;
}

void AnemometerSensor::begin() {
}

float AnemometerSensor::readWindSpeed() {
    int adcValue = analogRead(pin);
    float voltage = (adcValue / 4095.0) * 3.3;  // Convert ADC value to actual voltage

    // Clamp the voltage within the sensor's valid operating range
    if (voltage < 0) voltage = 0;
    if (voltage > 1.5) voltage = 1.5;

    // Convert voltage to wind speed (m/s)
    // Assuming 1.5V corresponds to a maximum wind speed of value calibrationFactor
    float windSpeed = (voltage / 1.5) * calibrationFactor;

    return windSpeed;
}