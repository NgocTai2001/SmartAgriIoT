#include "config/Config.h"
#include "core/Type.h"
#include "core/DataStore.h"
#include "core/DataStore.cpp"
#include "sensors/SensorManager.h"
#include "sensors/SensorManager.cpp"

SensorManager sensors(D4, A0, D1, D8, D3, D2, 1.5f);

DataStore store;
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("=== Read data from (ESP8266) ===");
  sensors.begin();

}

void loop() {
  delay(1000);
  
  EnvReading myhome (sensors.readTemperature() , sensors.readHumidity(), sensors.readWindSpeed(), sensors.readLightAnalog(), millis() / 1000);
  // store data after read all sensors.
  store.set(myhome);
  //printf data
  Serial.print("read data :"); Serial.println( store.toJsonString());

}