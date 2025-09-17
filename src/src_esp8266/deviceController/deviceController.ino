#include "DeviceController.h"

// WiFi & MQTT settings
const char* WIFI_SSID     = "YOUR_WIFI_SSID";
const char* WIFI_PASS     = "YOUR_WIFI_PASSWORD";
const char* MQTT_SERVER   = "192.168.1.100";
const int   MQTT_PORT     = 1883;
const char* MQTT_USER     = "";
const char* MQTT_PASS     = "";
const char* DEVICE_TOPIC  = "smartfarm/device/pump";

const int RELAY_PIN = D1;

DeviceController controller(
  WIFI_SSID,
  WIFI_PASS,
  MQTT_SERVER,
  MQTT_PORT,
  MQTT_USER,
  MQTT_PASS,
  DEVICE_TOPIC,
  RELAY_PIN
);

void setup() {
  controller.begin();
}

void loop() {
  controller.loop();
}