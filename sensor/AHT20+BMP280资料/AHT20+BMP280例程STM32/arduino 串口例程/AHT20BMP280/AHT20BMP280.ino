#include <Adafruit_AHTX0.h>// 引用库
#include <BMP280.h>
BMP280 bmp280;
Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);//初始化串口
  Serial.println("AHT20+BMP280 demo!");
  Wire.begin(); 
  bmp280.begin();//初始化BMP280
  if (! aht.begin()) {
    Serial.println("Could not find AHT20+BMP280? Check wiring");
    while (1) delay(10);
  }//初始化ATH20
  Serial.println("AHT10 or AHT20 found");
}

void loop() {
  uint32_t pressure = bmp280.getPressure();//BMP280填充气压
  sensors_event_t humidity, temp;//AHT20填充温湿度
  aht.getEvent(&humidity, &temp);
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
 Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println("Pa");
  delay(500);
}