#include "DeviceController.h"
#include <ArduinoJson.h>

DeviceController* _instance = nullptr;

// Constructor to initialize WiFi, MQTT, and relay settings
DeviceController::DeviceController(
  const char* ssid,
  const char* password,
  const char* mqtt_server,
  int mqtt_port,
  const char* mqtt_user,
  const char* mqtt_pass,
  const char* deviceTopic,
  int relayPin
) : ssid(ssid), password(password), mqtt_server(mqtt_server), mqtt_port(mqtt_port),
    mqtt_user(mqtt_user), mqtt_pass(mqtt_pass), deviceTopic(deviceTopic), relayPin(relayPin),
    client(espClient) {
  _instance = this;
}

void DeviceController::begin() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Default OFF (relay not active)

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callbackWrapper);
}

// Wrapper to pass MQTT messages to the instance's handleMessage
void DeviceController::callbackWrapper(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  if (_instance) {
    _instance->handleMessage(topic, message);
  }
}

// Handle received MQTT messages
void DeviceController::handleMessage(char* topic, String message) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  // Parse JSON data
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("JSON parsing failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Extract humidity value from JSON
  int humidity = doc["hum"];
  Serial.print("Humidity: ");
  Serial.println(humidity);

  // Control relay based on humidity
  if (humidity < 50) {
    digitalWrite(relayPin, LOW);  // Turn pump ON
    Serial.println("Pump ON (humidity < 50)");
  } else {
    digitalWrite(relayPin, HIGH); // Turn pump OFF
    Serial.println("Pump OFF (humidity >= 50)");
  }
}

// Try to reconnect to MQTT broker if disconnected
void DeviceController::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP_DEVICE", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      client.subscribe(deviceTopic);  // Subscribe to topic after reconnect
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Main loop to keep MQTT connection alive
void DeviceController::loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
