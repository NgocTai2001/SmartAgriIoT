#include "DHT11Sensor.h"

// Với NodeMCU/ESP8266: D4 = GPIO2. Nếu bạn dùng chân khác, sửa giá trị dưới đây.
#define DHT_PIN D4

DHT11Sensor sensor(DHT_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("=== DHT11 Reader (ESP8266) ===");
  sensor.begin();
}

void loop() {
  delay(2000);  // DHT11 cần delay giữa các lần đọc

  float t, h;
  if (sensor.read(t, h)) {
    Serial.print("Temperature: "); Serial.print(t); Serial.print(" °C  |  Humidity: ");
    Serial.print(h); Serial.println(" %");
  } else {
    Serial.println("Sensor read failed!");
  }
}