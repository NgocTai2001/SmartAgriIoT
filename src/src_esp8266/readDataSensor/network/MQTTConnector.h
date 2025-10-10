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
    MQTTConnector();

    void begin();
    void reconnect();
    void loop();
    void publish(const String& payload);
    bool isConnected();
};