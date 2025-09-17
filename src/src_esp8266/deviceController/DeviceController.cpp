#include "DeviceController.h"

DeviceController* _instance = nullptr;

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
  digitalWrite(relayPin, HIGH); // default OFF

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

void DeviceController::callbackWrapper(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  if (_instance) {
    _instance->handleMessage(topic, message);
  }
}

void DeviceController::handleMessage(char* topic, String message) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  if (message == "ON") {
    digitalWrite(relayPin, LOW);
    Serial.println("Device ON");
  } else if (message == "OFF") {
    digitalWrite(relayPin, HIGH);
    Serial.println("Device OFF");
  }
}

void DeviceController::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP_DEVICE", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      client.subscribe(deviceTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void DeviceController::loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}