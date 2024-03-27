/*************************
 *3区-ESP32              *
 *室外温湿度、降雨、气压   *
 *************************/
#include <Wire.h>
#include <WiFi.h>
#include <BMP280.h>
#include <esp_now.h>
#include <Adafruit_AHTX0.h>

//初始化I2C引脚-第一个设备
#define SDA_PIN_1 21
#define SCL_PIN_1 22
//初始化I2C引脚-第二个设备
#define SDA_PIN_2 15
#define SCL_PIN_2 4

/***************************
 *将ADDR模式设置为GND模式   *
 *ADDR引脚接地             *
 *其中地址为0010011(0x23)  *
 *若引脚接VCC              *
 *其中地址为1101100(0x5B)  *
 **************************/
#define ADDRESS_BH1750FVI 0x23  
#define ONE_TIME_H_RESOLUTION_MODE 0x20//32,try other numbers

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

//I2C接收的两字节数据
byte HighByte = 0;
byte LowByte = 0;

//I/O端口(To be continued)
const int TempPin=0;
const int AirHumPin=1;
const int VoltagePin=2;

//声明Aht20&Bmp20
Adafruit_AHTX0 aht;
BMP280 bmp280;

//检测是否初始化成功
void Detect(){
  //Aht20初始化
  while(!aht.begin()){
    Serial.println("Aht20 initial error!");
    delay(500);
  }

  //Bmp初始化
  while(!bmp280.begin()){
    Serial.println("Bmp280 initial error!");
    delay(500);
  }

  Serial.println("Aht20&Bmp280 initial successfully!");
}

void setup() {
  //初始化串口
  Serial.begin(115200);

  //初始化I2C总线
  Wire.begin(SDA_PIN_1, SCL_PIN_1);
  Wire.begin(SDA_PIN_2, SCL_PIN_2);

  // 初始化espnow
  WiFi.mode(WIFI_STA);
  while (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    delay(100);
  }

  //绑定数据接收端
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, ReceiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  //使能wifi
  peerInfo.ifidx = WIFI_IF_STA;

  //检查设备是否配对成功
  while (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    delay(100);
  }

  //初始化Aht20&Bmp280
  Detect();
}

void loop() {
  Wire.beginTransmission(ADDRESS_BH1750FVI); //"notify" the matching device

   Wire.write(ONE_TIME_H_RESOLUTION_MODE);   //set operation mode

   Wire.endTransmission();
}
