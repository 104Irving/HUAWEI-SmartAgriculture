/*******************
 *2区-ESP32        *
 *室外土壤湿度、电压 *
 *管理室外水泵      *
 *******************/

#include <WiFi.h>
#include <esp_now.h>

//espnow传输数据结构体
typedef struct EspNowDataSend{
  int SoilMoisture;      //土壤湿度
  int Voltage;           //电压
} EspNowDataSend;
EspNowDataSend SendData;

//espnow接收数据结构体
typedef struct EspNowDataReceive{
  int Bump;  //水泵
} EspNowDataReceive;
EspNowDataReceive ReceiveData;

//接收设备的MAC地址
uint8_t ReceiverAddress[] = {0x08, 0xD1, 0xF9, 0xE7, 0x2C, 0xE0};

//比对以判断是否启动
int cmp=0;

//I/O端口
const int BumpPin=0;
const int SoilMoisturePin=1;
const int VoltagePin=2;

//数据接收回调函数
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&ReceiveData, incomingData, sizeof(ReceiveData));
}

void setup() {
  //开启端口
  pinMode(BumpPin,OUTPUT);
  pinMode(SoilMoisturePin,INPUT);
  pinMode(VoltagePin,INPUT);

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

  //启用接收数据回调函数
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  //比对数据并决定是否更改水泵状态
  if(ReceiveData.Bump!=cmp){
    cmp=ReceiveData.Bump;
    if(cmp){
      digitalWrite(BumpPin,HIGH);
    }
    else{
      digitalWrite(BumpPin,LOW);
    }
  }

  //读取传感器数据(To be continued)
  SendData.Voltage=analogRead(VoltagePin);

}