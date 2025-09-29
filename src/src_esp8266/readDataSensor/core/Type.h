#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

struct EnvReading {
  float temperatureC = NAN;   // temp (°C)
  float humidity     = NAN;   // hum  (%)
  float windSpeed    = NAN;   // wind (m/s)
  int   lightPercent = 0;    // light (0..100)
  unsigned long ts   = 0;     // timestamp millis() 
  int Soil         = NAN;

  EnvReading(float t =0, float h = 0, float w = 0, int l = 0, unsigned long timestamp = 0, int S = 0)
    : temperatureC(t), humidity(h), windSpeed(w),
      lightPercent(l), ts(timestamp), Soil(S) {}

  // data to json that connect to MQTT sever
  void toJsonDoc(JsonDocument& doc) const {
    doc.clear();
    doc["ts"] = ts;
    if (!isnan(temperatureC)) doc["temp"]  = temperatureC;
    if (!isnan(humidity))     doc["hum"]   = humidity;
    if (!isnan(windSpeed))    doc["wind"]  = windSpeed;
    if (lightPercent >= 0)    doc["light"] = lightPercent;
    if (!isnan(Soil))         doc["Soil"]   = Soil;
  }

  // get data to String 
  String toJsonString() const {
    StaticJsonDocument<256> d; toJsonDoc(d);
    String out; serializeJson(d, out); return out;
  }
};
