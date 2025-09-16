#include "DHT11Sensor.h"

#define DHTTYPE DHT11

DHT11Sensor::DHT11Sensor(uint8_t pin)
: _pin(pin), _dht(pin, DHTTYPE) {}

void DHT11Sensor::begin() {
  _dht.begin();
}

bool DHT11Sensor::read(float &temperatureC, float &humidity) {
  humidity     = _dht.readHumidity();
  temperatureC = _dht.readTemperature();   // °C
  if (isnan(humidity) || isnan(temperatureC)) return false;
  return true;
}