#pragma once
#include <WiFi.h>
#include "config/Config.h"

class WiFiConnector {
public:
    void begin();
    bool isConnected();
    void reconnect();
};