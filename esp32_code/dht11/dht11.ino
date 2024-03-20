#include <Arduino.h>
#include <DHT.h>
 
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 4 
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  dht.begin();
}
 
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Read temperature as Celsius (the default)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(1000);
    return;
  }
  // Check if any reads failed and exit early (to try again).

  Serial.print("湿度:");
  Serial.print(h);
  Serial.println("％");

  Serial.print("温度:");
  Serial.print(t);
  Serial.print("℃");

  Serial.print("/");
  Serial.print(f);
  Serial.println("℉");

  delay(10000);
}

