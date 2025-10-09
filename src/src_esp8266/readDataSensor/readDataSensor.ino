#include "config/Config.h"
#include "core/Type.h"
#include "core/DataStore.h"
#include "core/DataStore.cpp"
#include "sensors/SensorManager.h"
#include "sensors/SensorManager.cpp"
#include <WiFi.h>
#include <PubSubClient.h>
#include "network/WiFiConnector.h"
#include "network/MQTTConnector.h"

// ==============================
// Object initialization
// ==============================
WiFiConnector wifi;    // Handles WiFi connection logic
MQTTConnector mqtt;    // Handles MQTT connection logic
DataStore store;       // Stores sensor readings temporarily
SensorManager sensors( // Manages all sensors on the ESP32
  PIN_DHT,
  PIN_SOIL_ANALOG,
  PIN_SOIL_DIGITAL,
  PIN_LIGHT_ANALOG,
  PIN_LIGHT_DIGITAL,
  PIN_WIND,
  WIND_CALIBRATION
);

// ==============================
// Setup function (runs once)
// ==============================
void setup() {
  Serial.begin(115200);
  Serial.println("\n=== Smart Agriculture Internet of Things ===");
  sensors.begin();   // Initialize all sensors
  wifi.begin();      // Connect to WiFi network
  mqtt.begin();      // Configure and connect to MQTT broker
}

// ==============================
// Main loop (runs repeatedly)
// ==============================
void loop() {
  // Ensure WiFi and MQTT connections remain active
  wifi.reconnect();
  mqtt.loop();

  delay(1000); // Sampling interval (1 second)

  // Read all sensor values
  EnvReading data(
    sensors.readTemperature(),
    sensors.readHumidity(),
    sensors.readWindSpeed(),
    sensors.readLightAnalog(),
    millis() / 1000,  // Timestamp in seconds
    sensors.readSoilAnalog()
  );

  // Store and convert readings to JSON
  store.set(data);
  String json = store.toJsonString();

  // Print sensor data to Serial Monitor
  Serial.println(json);

  // Publish JSON data to MQTT topic
  mqtt.publish(json);
}