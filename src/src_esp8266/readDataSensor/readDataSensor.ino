#include "sensors/DHT11Sensor.h"
#include "sensors/DHT11Sensor.cpp"
#include "core/Type.h"
#include "core/DataStore.h"
#include "core/DataStore.cpp"

#define DHT_PIN D4

DHT11Sensor sensor(DHT_PIN);
DataStore store;
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("=== DHT11 Reader (ESP8266) ===");
  sensor.begin();

}

void loop() {
  delay(2000);

  float t, h;
  if (sensor.read(t, h)) {

  EnvReading myhome ( t, h, 1.2 ,80, millis() / 1000);

  //store data after read all sensors.
  store.set(myhome);
  
   //printf data before send to MQTT 
  Serial.println("[LATEST]");
  Serial.println(myhome.toJsonString());
  
  } else {

    Serial.println("Sensor read failed!");

  }
}