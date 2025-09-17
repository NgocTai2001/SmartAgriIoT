#include "config/Config.h"
#include "sensors/DHT11Sensor.h"
#include "sensors/DHT11Sensor.cpp"
#include "core/Type.h"
#include "core/DataStore.h"
#include "core/DataStore.cpp"
#include "sensors/YL69Sensor.h"
#include "sensors/YL69Sensor.cpp"
#include "sensors/LM393LDRSensor.h"
#include "sensors/LM393LDRSensor.cpp"
#include "sensors/AnemometerSensor.h"
#include "sensors/AnemometerSensor.cpp"

DHT11Sensor sensor(PIN_DHT);
YL69Sensor soilSensor(A0, D1);
LM393LDRSensor lightSensor(A0, D2);
// Example: 1 pulse per rotation, 1 rotation = 2.4 km/h (~0.67 m/s)
// calibrationFactor = pulses per second per m/s
AnemometerSensor windSensor(D3, 1.5f);

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
  int valueSoil = soilSensor.readAnalog();
  bool isWet = soilSensor.readDigital();
  int valueLight = lightSensor.readAnalog();
  bool isDark = lightSensor.readDigital();
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

//printf data of Soil 
  Serial.print("Analog: ");
  Serial.print(valueSoil);
  Serial.print(" | Digital: ");
  Serial.println(isWet ? "Wet" : "Dry");
//printf data of Light 
  Serial.print("Analog: ");
  Serial.print(valueLight);
  Serial.print(" | Digital: ");
  Serial.println(isDark ? "Dark" : "Bright");

//printf data of Wind
  float speed = windSensor.readWindSpeed();
  if (speed >= 0) {
    Serial.print("Wind Speed: ");
    Serial.print(speed);
    Serial.println(" m/s");
  }

}