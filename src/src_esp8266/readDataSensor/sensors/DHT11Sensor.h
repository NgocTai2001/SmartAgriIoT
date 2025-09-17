#pragma once
#include <Arduino.h>
#include <DHT.h>

class DHT11Sensor {
public:
  explicit DHT11Sensor(uint8_t pin);
  void begin();
  float readTemperature();
  float readHumidity();
private:
  uint8_t _pin;
  DHT _dht;
};  