#pragma once
#include <Arduino.h>

/* ================== DEVICE INFO ================== */
#ifndef DEVICE_ID
#define DEVICE_ID "esp8266-garden-01"
#endif

/* ================== WIFI ================== */
#ifndef WIFI_SSID
#define WIFI_SSID     "VIETTEL_Vyvy"
#endif
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "Vyvyvyvy"
#endif

/* ================== PIN MAPPING (ESP8266 NodeMCU) ==================
 * D4 = GPIO2, D1 = GPIO5, etc. Adjust according to your hardware.
 */
#ifndef PIN_DHT
#define PIN_DHT       D4      // DHT11 (Temperature/Humidity)
#endif

#ifndef PIN_WIND
#define PIN_WIND      D6      // Anemometer pulse input (interrupt/pulse)
#endif

#ifndef PIN_LIGHT_A
#define PIN_LIGHT_A   A0      // Analog light sensor (LDR)
#endif

#ifndef PIN_PUMP
#define PIN_PUMP      D1      // Relay/MOSFET to control water pump
#endif

/* Most relay modules are active LOW (LOW=ON). For MOSFET: HIGH=ON. */
#ifndef PUMP_ACTIVE_LOW
#define PUMP_ACTIVE_LOW true
#endif

/* ================== TIMING ================== */
#ifndef READ_INTERVAL_MS
#define READ_INTERVAL_MS      2000UL  // sensor reading interval
#endif

#ifndef PRINT_INTERVAL_MS
#define PRINT_INTERVAL_MS     5000UL  // Serial print interval
#endif

#ifndef MQTT_TELEMETRY_INTERVAL_MS
#define MQTT_TELEMETRY_INTERVAL_MS 10000UL // publish interval (if using MQTT later)
#endif

/* ================== CONTROL THRESHOLDS (for pump logic) ================== */
#ifndef SOIL_THRESHOLD_PERCENT
#define SOIL_THRESHOLD_PERCENT  35    // below threshold -> turn pump ON
#endif

#ifndef SOIL_TARGET_AFTER_WATERING
#define SOIL_TARGET_AFTER_WATERING 55 // above threshold -> turn pump OFF
#endif

#ifndef PUMP_MIN_ON_MS
#define PUMP_MIN_ON_MS         (15UL * 1000) // minimum ON duration
#endif

#ifndef PUMP_MIN_OFF_MS
#define PUMP_MIN_OFF_MS        (20UL * 1000) // minimum OFF duration
#endif

/* ================== SENSOR CALIBRATION ================== */
// Light analog 0..1023 -> % (adjust depending on LDR circuit)
#ifndef LIGHT_RAW_DARK
#define LIGHT_RAW_DARK  100    // ADC value when dark
#endif
#ifndef LIGHT_RAW_BRIGHT
#define LIGHT_RAW_BRIGHT 900   // ADC value when very bright
#endif

// (For future soil analog sensor calibration)
// #define SOIL_RAW_DRY  900
// #define SOIL_RAW_WET  300

/* ================== MQTT (reserved for later use) ================== */
#ifndef MQTT_HOST
#define MQTT_HOST "192.168.1.100"
#endif
#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif
#ifndef MQTT_BASE_TOPIC
#define MQTT_BASE_TOPIC "smart_garden"
#endif