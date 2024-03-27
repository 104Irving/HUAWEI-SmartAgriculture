/*******************
 *2区-ESP32        *
 *室外土壤湿度、电压 *
 *管理室外水泵      *
 *Ciallo!          *
 *******************/

#include <WiFi.h>
#include <esp_now.h>

//任务〇
TaskHandle_t Task0;

//espnow传输数据结构体
typedef struct EspNowDataSend{
  int SoilMoisture;      //土壤湿度
  double Voltage;        //电池电压
  int BatteryLevel;      //电池电量
} EspNowDataSend;
EspNowDataSend SendData;

//espnow接收数据结构体
typedef struct EspNowDataReceive{
  int Bump;              //水泵
} EspNowDataReceive;
EspNowDataReceive ReceiveData;

//接收设备的MAC地址
uint8_t ReceiverAddress[] = {0x08, 0xD1, 0xF9, 0xE7, 0x2C, 0xE0};

//比对以判断是否启动
int cmp=0;

//I/O端口
const int BumpPin=0;
const int SoilMoisturePin=35;
const int VoltagePin=34;

//数据接收回调函数
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&ReceiveData, incomingData, sizeof(ReceiveData));
}

/************************************
 *计算电池电压及电量                  *
 *使用esp32测量电池电压的20%并进行处理 *
 *得到实际电压与电池电量              *
 ************************************/
void VolChange(double V){
  SendData.Voltage = -3.3126889904968743e-18*V*V*V*V*V*V*V\
                     +1.623217605075953e-14*V*V*V*V*V*V\
                     -3.3719331192434486e-11*V*V*V*V*V\
                     +3.847999653156838e-8*V*V*V*V\
                     -0.00002604499123955503*V*V*V\
                     +0.010452452154782833*V*V\
                     -2.3016342267679173*V\
                     +214.85012707853883;
  SendData.Voltage *= 5;
  SendData.BatteryLevel = 100*(SendData.Voltage-3)/1.2;
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

  //使用核心0, 读取土壤湿度及电池电压数据
  xTaskCreatePinnedToCore(
                    Task0code,   /* Task function. */
                    "Task0",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task0,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(100);
}

void Task0code(void * pvParameters){
  //读取电池电压数据并处理
  double V=analogRead(VoltagePin);
  VolChange(V);

  //读取土壤湿度数据并处理
  double SM=analogRead(SoilMoisturePin);
  SendData.SoilMoisture=(SM,2200,1200,0,100);

  //发送数据(每十秒发送一次)
  esp_now_send(ReceiverAddress, (uint8_t *) &SendData, sizeof(SendData));
  delay(10000);
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
}