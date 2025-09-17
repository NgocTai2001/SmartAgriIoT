#include "SensorManager.h"

SensorManager::SensorManager(int dhtPin, int yl69Analog, int yl69Digital, int ldrAnalog, int ldrDigital, int anePin, float aneFactor)
  : dht11(dhtPin),
    yl69(yl69Analog, yl69Digital),
    ldr(ldrAnalog, ldrDigital),
    anemometer(anePin, aneFactor) {}

void SensorManager::begin() {
  dht11.begin();
  anemometer.begin();
}

// DHT11
float SensorManager::readTemperature() {
  return dht11.readTemperature();
}
float SensorManager::readHumidity() {
  return dht11.readHumidity();
}

// YL69
int SensorManager::readSoilAnalog() {
  return yl69.readSoilAnalog();
}
bool SensorManager::readSoilDigital() {
  return yl69.readSoilDigital();
}

// LDR
int SensorManager::readLightAnalog() {
  return ldr.readLightAnalog();
}
bool SensorManager::readLightDigital() {
  return ldr.readLightDigital();
}

// Anemometer
float SensorManager::readWindSpeed() {
  return anemometer.readWindSpeed();
}