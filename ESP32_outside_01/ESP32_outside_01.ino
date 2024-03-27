/*************************
 *3区-ESP32              *
 *室外温湿度、降雨、气压   *
 *************************/
#include <WiFi.h>
#include <esp_now.h>

//espnow传输数据结构体
typedef struct EspNowDataSend{
  int Temperature;    //温度
  int AirHumidity;    //空气湿度
  int Rain;           //降雨
  int AtmoPre;        //气压
} EspNowDataSend;
EspNowDataSend SendData;

//接收设备的MAC地址
uint8_t ReceiverAddress[] = {0x08, 0xD1, 0xF9, 0xE7, 0x2C, 0xE0};

//I/O端口(To be continued)
const int TempPin=0;
const int SoilMoisturePin=1;
const int VoltagePin=2;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
