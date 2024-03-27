#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>

/***************************
 *将ADDR模式设置为GND模式   *
 *ADDR引脚接地             *
 *其中地址为0010011(0x23)  *
 *若引脚接VCC              *
 *其中地址为1101100(0x5B)  *
 **************************/
#define ADDRESS_BH1750FVI 0x23  
#define ONE_TIME_H_RESOLUTION_MODE 0x20

void setup() {
  // put your setup code here, to run once:
Light intensity
}

void loop() {
  //设置GY-30为单次L分辨率模式
  Wire.beginTransmission(ADDRESS_BH1750FVI);
  Wire.write(ONE_TIME_H_RESOLUTION_MODE);
  Wire.endTransmission();
  delay(150);

  //读取I2C总线传输的数据并处理(光强数据)
  byte HighByte = 0;
  byte LowByte = 0;
  Wire.requestFrom(ADDRESS_BH1750FVI,2);
  HighByte = Wire.read();
  LowByte = Wire.read();
  SendData.
}
