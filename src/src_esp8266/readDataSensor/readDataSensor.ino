#include "config/Config.h"
#include "core/Type.h"
#include "core/DataStore.h"
#include "core/DataStore.cpp"
#include "sensors/SensorManager.h"
#include "sensors/SensorManager.cpp"
#include <WiFi.h>
#include <PubSubClient.h>

// =========================
// WiFi configuration
// =========================
const char* ssid = "VIETTEL_Vyvy";
const char* password = "Vyvyvyvy";

// =========================
// MQTT configuration (broker running on Raspberry Pi 3)
// =========================
const char* mqtt_server = "192.168.1.16";   // Replace with the actual Raspberry Pi IP
const int   mqtt_port   = 1883;
const char* mqtt_topic  = "dev/test";
const char* mqtt_user   = "Tnt28122001";
const char* mqtt_pass   = "Tnt28122001!";

// =========================
// Create WiFi and MQTT clients
// =========================
WiFiClient espClient;
PubSubClient client(espClient);
DataStore store;
SensorManager sensors(
  4,   // DHT11 data pin
  34,  // YL69 analog output (ADC1)
  25,  // YL69 digital output
  35,  // LDR analog output (ADC1)
  26,  // LDR digital output
  27,  // Anemometer signal pin
  0.5f // Calibration factor for wind speed
);


// =========================
// Connect to WiFi
// =========================
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// =========================
// Reconnect to MQTT if disconnected
// =========================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // Connect with username/password
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("Connected to MQTT broker");
      // Subscribe to a topic if you need to receive commands from broker
      // client.subscribe("dev/control");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" => try again in 5 seconds");
      delay(5000);
    }
  }
}

// =========================
// Setup function
// =========================
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("=== Read data from ESP32 ===");

  sensors.begin();                 // Initialize sensors
  setup_wifi();                    // Connect to WiFi
  client.setServer(mqtt_server, mqtt_port);  // Setup MQTT broker info
}

// =========================
// Main loop
// =========================
void loop() {
  if (!client.connected()) {
    reconnect(); // Ensure MQTT connection
  }
  client.loop();

  delay(1000); // Sampling interval

  // Read data from sensors
  EnvReading myhome(
    sensors.readTemperature(),
    sensors.readSoilAnalog(),
    sensors.readWindSpeed(),
    sensors.readLightAnalog(),
    millis() / 1000  // Timestamp in seconds
  );

  store.set(myhome); // Save reading in datastore

  // Convert to JSON string
  String jsonData = store.toJsonString();

  Serial.print("Read data: ");
  Serial.println(jsonData);

  // Publish JSON to MQTT topic
  client.publish(mqtt_topic, jsonData.c_str());
}
