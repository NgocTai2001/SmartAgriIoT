#pragma once
#include <PubSubClient.h>
#include "config/Config.h"

class MQTTConnector {
private:
    WiFiClient espClient;
    PubSubClient client;
    const char* server;
    int port;
    const char* user;
    const char* pass;
    const char* topic;

public:
    MQTTConnector()
        : client(espClient),
          server(MQTT_SERVER),
          port(MQTT_PORT),
          user(MQTT_USER),
          pass(MQTT_PASS),
          topic(MQTT_TOPIC) {}

    void begin() {
        client.setServer(server, port);
    }

    void reconnect() {
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

    void loop() {
        if (!client.connected()) reconnect();
        client.loop();
    }

    void publish(const String& payload) {
        client.publish(topic, payload.c_str());
    }

    bool isConnected()  {
        return client.connected();
    }
};