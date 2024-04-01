#include <WiFi.h>
#include <esp_now.h>

//WiFi账号及密码
const char *ssid="Ginoson";        //WiFi账号
const char *password="20050601";   //WiFi密码

//MQTT Broker(订阅主题未完成)
const char *mqtt_broker="121.48.197.19";  //IP地址
const int mqtt_port=1883;                 //端口
const char *mqtt_username="ESP32_00";     //用户名
const char *mqtt_password="a12345678";    //密码
const char *topic="010101";

//espnow通信的单片机MAC地址
uint8_t ReceiverAddress_00[]={0x08, 0xD1, 0xF9, 0xE6, 0xCC, 0xEC};        //室外 土壤湿度,电压电量/室外水泵
uint8_t ReceiverAddress_01[]={0x08, 0xD1, 0xF9, 0x3B, 0x10, 0xA8};        //室外 温湿度,降雨,气压
uint8_t ReceiverAddress_02[]={0x08, 0xD1, 0xF9, 0xE7, 0x2C, 0xE0};        //室内 温湿度,光强,水箱及培养槽水位/室内水泵,LED,天窗,风扇

//用于espnow初始化(本机发送数据)
inline void EspNowConnect(){
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

  // 初始化espnow
  WiFi.mode(WIFI_STA);
  while (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    delay(100);
  }
}

void setup() {
  A
}

void loop() {
  B
}
