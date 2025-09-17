#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

struct EnvReading {
  float temperatureC = NAN;   // temp (°C)
  float humidity     = NAN;   // hum  (%)
  float windSpeed    = NAN;   // wind (m/s)
  int   lightPercent = -1;    // light (0..100)
  unsigned long ts   = 0;     // timestamp millis() 

  EnvReading()
    : temperatureC(NAN), humidity(NAN), windSpeed(NAN),
      lightPercent(-1), ts(0) {}

  EnvReading(float t, float h, float w, int l, unsigned long timestamp = 0)
    : temperatureC(t), humidity(h), windSpeed(w),
      lightPercent(l), ts(timestamp) {}

  // data to json that connect to MQTT sever
  void toJsonDoc(JsonDocument& doc) const {
    doc.clear();
    doc["ts"] = ts;
    if (!isnan(temperatureC)) doc["temp"]  = temperatureC;
    if (!isnan(humidity))     doc["hum"]   = humidity;
    if (!isnan(windSpeed))    doc["wind"]  = windSpeed;
    if (lightPercent >= 0)    doc["light"] = lightPercent;
  }

  // get data to String 
  String toJsonString() const {
    StaticJsonDocument<256> d; toJsonDoc(d);
    String out; serializeJson(d, out); return out;
  }
};
