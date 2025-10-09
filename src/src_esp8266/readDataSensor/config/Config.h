#pragma once
#include <Arduino.h>

/* ================== DEVICE INFO ================== */
#ifndef DEVICE_ID
#define DEVICE_ID "ESP32 Smart Garden"
#endif

/* ================== WIFI CONFIG ================== */
#ifndef WIFI_SSID
#define WIFI_SSID     "VIETTEL_Vyvy"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "Vyvyvyvy"
#endif

/* ================== MQTT CONFIG ================== */
#ifndef MQTT_SERVER
#define MQTT_SERVER "raspberrypi.local"   // Broker hostname or IP (e.g. "192.168.1.10")
#endif

#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

#ifndef MQTT_TOPIC
#define MQTT_TOPIC "dev/test"
#endif

#ifndef MQTT_USER
#define MQTT_USER "Tnt28122001"
#endif

#ifndef MQTT_PASS
#define MQTT_PASS "Tnt28122001!"
#endif

/* ================== PIN MAPPING ================== */
// DHT11
#ifndef PIN_DHT
#define PIN_DHT 4
#endif

// Soil Moisture Sensor (YL-69)
#ifndef PIN_SOIL_ANALOG
#define PIN_SOIL_ANALOG 34
#endif

#ifndef PIN_SOIL_DIGITAL
#define PIN_SOIL_DIGITAL 25
#endif

// Light Sensor (LDR)
#ifndef PIN_LIGHT_ANALOG
#define PIN_LIGHT_ANALOG 35
#endif

#ifndef PIN_LIGHT_DIGITAL
#define PIN_LIGHT_DIGITAL 26
#endif

// Anemometer (Wind Speed)
#ifndef PIN_WIND
#define PIN_WIND 32
#endif

#ifndef WIND_CALIBRATION
#define WIND_CALIBRATION 150
#endif