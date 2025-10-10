#include "MQTTConnector.h"
#include <Arduino.h>

MQTTConnector::MQTTConnector()
    : client(espClient),
      server(MQTT_SERVER),
      port(MQTT_PORT),
      user(MQTT_USER),
      pass(MQTT_PASS),
      topic(MQTT_TOPIC) {}

void MQTTConnector::begin() {
    client.setServer(server, port);
}

void MQTTConnector::reconnect() {
    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");
        String clientId = "ESP32Client-" + String(random(0xffff), HEX);

        if (client.connect(clientId.c_str(), user, pass)) {
            Serial.println("Connected to MQTT broker");
        } else {
            Serial.printf("Failed, rc=%d. Retry in 5s\n", client.state());
            delay(5000);
        }
    }
}

void MQTTConnector::loop() {
    if (!client.connected()) reconnect();
    client.loop();
}

void MQTTConnector::publish(const String& payload) {
    client.publish(topic, payload.c_str());
}

bool MQTTConnector::isConnected() {
    return client.connected();
}
