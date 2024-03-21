#include <Arduino.h>
#include <DHT.h> //dht库
 
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 4 //定义dht信号引脚
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200); //设置串口波特率
  dht.begin(); //启动dht
}
 
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); //读取摄氏度
  float f = dht.readTemperature(true); //读取华氏度
  

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(1000);
    return;
  }
  // 检查是否有数据读取失败，并重新尝试，间隔1s

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
  //上报间隔10s
}

