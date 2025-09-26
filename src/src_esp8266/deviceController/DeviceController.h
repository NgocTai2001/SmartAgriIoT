#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class DeviceController {
  private:
    const char* ssid;
    const char* password;
    const char* mqtt_server;
    int mqtt_port;
    const char* mqtt_user;
    const char* mqtt_pass;
    const char* deviceTopic;
    int relayPin;

    WiFiClient espClient;
    PubSubClient client;
    unsigned long lastMessageTime;  
    static const unsigned long DATA_TIMEOUT = 30000; // 30 giây
    static void callbackWrapper(char* topic, byte* payload, unsigned int length);
    void handleMessage(char* topic, String message);

  public:
    DeviceController(
      const char* ssid,
      const char* password,
      const char* mqtt_server,
      int mqtt_port,
      const char* mqtt_user,
      const char* mqtt_pass,
      const char* deviceTopic,
      int relayPin
    );

    void begin();
    void loop();
    void reconnect();
};

#endif