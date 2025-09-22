#include "DeviceController.h"

// =========================
// WiFi configuration
// =========================
const char* WIFI_SSID  = "VIETTEL_Vyvy";
const char* WIFI_PASS  = "Vyvyvyvy";

// =========================
// MQTT configuration (broker running on Raspberry Pi 3)
// =========================
const char* MQTT_SERVER  = "192.168.1.16";   // Replace with Raspberry Pi IP
const int   MQTT_PORT    = 1883;             // MQTT default port
const char* MQTT_USER    = "Tnt28122001";    // MQTT username
const char* MQTT_PASS    = "Tnt28122001!";   // MQTT password
const char* DEVICE_TOPIC = "dev/test";       // Topic to subscribe/publish

// =========================
// LED configuration (using built-in LED on ESP8266)
// =========================
const int RELAY_PIN = D0;

// Initialize DeviceController with WiFi + MQTT + LED parameters
DeviceController controller(
  WIFI_SSID,     // WiFi SSID
  WIFI_PASS,     // WiFi password
  MQTT_SERVER,   // MQTT broker address (Raspberry Pi)
  MQTT_PORT,     // MQTT port
  MQTT_USER,     // MQTT username
  MQTT_PASS,     // MQTT password
  DEVICE_TOPIC,  // Topic for receiving/sending data
  RELAY_PIN        // Relay pin to control
);

void setup() {
  controller.begin();  // Connect WiFi + MQTT + initialize LED
}

void loop() {
  controller.loop();   // Keep listening for MQTT messages and handle them
}
