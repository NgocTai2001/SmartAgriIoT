#include "DeviceController.h"
#include "ThingsBoardService.h"

// =========================
// WiFi configuration
// =========================
const char* WIFI_SSID  = "VIETTEL_Vyvy";
const char* WIFI_PASS  = "Vyvyvyvy";

// =========================
// MQTT configuration (broker running on Raspberry Pi 3)
// =========================
const char* MQTT_SERVER  = "raspberrypi.local";   
const int   MQTT_PORT    = 1883;
const char* MQTT_USER    = "Tnt28122001";
const char* MQTT_PASS    = "Tnt28122001!";
const char* DEVICE_TOPIC = "dev/test";

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
  Serial.begin(115200);
  controller.begin();  // Connect WiFi + MQTT + initialize LED
  TB_Init();
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

}

void loop() {

  TB_Loop(); 
  if (autoModeFlag) {
    Serial.println("CHE DO MANUAL");
    if(pumpStateFlag)
    {
      Serial.println("Bat Bom Tu ThingBoard");
      digitalWrite(RELAY_PIN, LOW);
    }
    else{
      Serial.println("Tat Bom Tu ThingBoard");
       digitalWrite(RELAY_PIN, HIGH); // OFF mặc định
    }
  } 
  else {
    controller.loop();   // MQTT
    Serial.println("CHE DO TU DONG");
  }
  delay(500);
}
