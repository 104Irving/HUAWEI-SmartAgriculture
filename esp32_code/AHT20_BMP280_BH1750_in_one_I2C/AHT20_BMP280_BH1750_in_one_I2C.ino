#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <BMP280.h>

#define SDA_PIN_1 21  // 第一个传感器的SDA引脚
#define SCL_PIN_1 22  // 第一个传感器的SCL引脚

#define SDA_PIN_2 15  // 第二个传感器的SDA引脚
#define SCL_PIN_2 4   // 第二个传感器的SCL引脚


#define ADDRESS_BH1750FVI 0x23  //ADDR="L" for this module
#define ONE_TIME_H_RESOLUTION_MODE 0x20

//One Time H-Resolution Mode:

//Resolution = 1 lux

//Measurement time (max.) = 180ms

//Power down after each measurement

byte highByte = 0;

byte lowByte = 0;

unsigned int sensorOut = 0;

unsigned int illuminance = 0;


Adafruit_AHTX0 aht;
BMP280 bmp280;

void setup() {
  Wire.begin(SDA_PIN_1, SCL_PIN_1); // 初始化第一条I2C总线
  Wire.begin(SDA_PIN_2, SCL_PIN_2); // 初始化第二条I2C总线

  Serial.begin(115200);//初始化串口
  Serial.println("AHT20+BMP280 demo!");
  Wire.begin(); 
  bmp280.begin();//初始化BMP280
  if (! aht.begin()) {
    Serial.println("Could not find AHT20+BMP280? Check wiring");
    while (1) delay(10);
  }  //初始化ATH20
  Serial.println("AHT10 or AHT20 found");
}

void loop(){

   Wire.beginTransmission(ADDRESS_BH1750FVI); //"notify" the matching device

   Wire.write(ONE_TIME_H_RESOLUTION_MODE);   //set operation mode

   Wire.endTransmission();

   delay(180);

   Wire.requestFrom(ADDRESS_BH1750FVI, 2); //ask Arduino to read back 2 bytes from the sensor

   highByte = Wire.read(); // get the high byte

   lowByte = Wire.read(); // get the low byte

   sensorOut = (highByte<<8)|lowByte;

   illuminance = sensorOut/1.2;
   

  uint32_t pressure = bmp280.getPressure();//BMP280填充气压
  sensors_event_t humidity, temp;//AHT20填充温湿度

  aht.getEvent(&humidity, &temp);


  Serial.print("光照强度："); Serial.print(illuminance);  Serial.println("lux");
  Serial.print("温度: "); Serial.print(temp.temperature); Serial.println("℃");
  Serial.print("湿度: "); Serial.print(humidity.relative_humidity); Serial.println("％");
  Serial.print("气压: ");
  Serial.print(pressure/1000);
  Serial.println("KPa");
  delay(1000);
}