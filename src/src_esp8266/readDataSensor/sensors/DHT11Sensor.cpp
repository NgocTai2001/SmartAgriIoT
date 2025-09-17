#include "DHT11Sensor.h"

#define DHTTYPE DHT11

DHT11Sensor::DHT11Sensor(uint8_t pin)
: _pin(pin), _dht(pin, DHTTYPE) {}

void DHT11Sensor::begin() {
  _dht.begin();
}

float DHT11Sensor::readTemperature() {
  return _dht.readTemperature();
}

float DHT11Sensor::readHumidity() {
  return _dht.readHumidity();
}
