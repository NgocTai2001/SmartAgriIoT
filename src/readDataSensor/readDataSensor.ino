#include "DHT.h"

#define DHTPIN D4        // Pin where the DHT sensor is connected
#define DHTTYPE DHT11    // Define the type of sensor used (DHT11)
DHT dht(DHTPIN, DHTTYPE);

// Function to initialize sensor
void initSensor() {
  dht.begin();
  Serial.println("DHT11 sensor initialized.");
}

// Function to read temperature
float readTemperature() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Error: Failed to read temperature!");
    return -1; // Return -1 if failed
  }
  return t;
}

// Function to read humidity
float readHumidity() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Error: Failed to read humidity!");
    return -1; // Return -1 if failed
  }
  return h;
}

// Function to display data
void displayData(float t, float h) {
  if (t == -1 || h == -1) {
    Serial.println("Invalid sensor data!");
    return;
  }
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C  |  Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Testing DHT11 sensor with ESP8266...");
  initSensor();
}

void loop() {
  delay(2000);  // Delay between reads

  float temperature = readTemperature();
  float humidity = readHumidity();

  displayData(temperature, humidity);
}
