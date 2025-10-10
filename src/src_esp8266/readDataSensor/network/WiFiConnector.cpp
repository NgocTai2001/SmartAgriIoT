#include "WiFiConnector.h"
#include <Arduino.h> 

void WiFiConnector::begin() {
    Serial.printf("\nConnecting to WiFi: %s\n", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int retry = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if (++retry > 60) { // 30s timeout
            Serial.println("\nWiFi connection failed!");
            return;
        }
    }

    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

bool WiFiConnector::isConnected() {
    return (WiFi.status() == WL_CONNECTED);
}

void WiFiConnector::reconnect() {
    if (!isConnected()) {
        Serial.println("Reconnecting WiFi...");
        WiFi.disconnect();
        WiFi.reconnect();
    }
}
