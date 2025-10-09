#pragma once
#include <WiFi.h>
#include "config/Config.h"

class WiFiConnector {
public:
    void begin() {
        Serial.printf("\nConnecting to WiFi: %s\n", WIFI_SSID);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        int retry = 0;
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
            if (++retry > 60) { // 30s timeout
                Serial.println("\n WiFi connection failed!");
                return;
            }
        }

        Serial.println("\n WiFi connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }

    bool isConnected()  {
        return (WiFi.status() == WL_CONNECTED);
    }

    void reconnect() {
        if (!isConnected()) {
            Serial.println("Reconnecting WiFi...");
            WiFi.disconnect();
            WiFi.reconnect();
        }
    }
};