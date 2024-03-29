/*******************
 *2区-ESP32        *
 *室外土壤湿度、电压 *
 *管理室外水泵      *
 *Ciallo :)        *
 *******************/
#include <WiFi.h>
#include <esp_now.h>

//任务〇
TaskHandle_t Task0;

//espnow传输数据结构体
typedef struct EspNowDataSend{
  int SoilMoisture;            //土壤湿度
  double Voltage;              //电池电压
  int BatteryLevel;            //电池电量
} EspNowDataSend;
EspNowDataSend SendData;

//espnow接收数据结构体
typedef struct EspNowDataReceive{
  struct bump{
    int State;                   //水泵操作模式 0->由单片机自主控制;1->手动控制;2->计划
    int Switch;                  //水泵开关 0->关闭;1->开启
    int Time;                    //单次灌溉时长,默认为3s
    int Interval;                //计划操作时,间隔时间(单位:ms)
  };
  bump Bump;
} EspNowDataReceive;
EspNowDataReceive ReceiveData;

//接收设备的MAC地址
uint8_t ReceiverAddress[] = {0x08, 0xD1, 0xF9, 0xE7, 0x2C, 0xE0};

//比对以判断水泵状态是否改变
int cmp=3;

//I/O端口
const int BumpPin=0;           //水泵针脚
const int SoilMoisturePin=35;  //土壤湿度传感器针脚
const int VoltagePin=34;       //电池电压针脚

//设置土壤湿度传感器采样数量
const int NumRead=5;           //采样数量
int MoistRead[NumRead];        //存储样本
int Point=0;                   //指示目前最新数据
unsigned long long TimeStamp;  //时间戳,用于控制灌溉时间

//数据接收回调函数
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&ReceiveData, incomingData, sizeof(ReceiveData));
}

/************************************
 *计算电池电压及电量                  *
 *使用esp32测量电池电压的20%并进行处理 *
 *得到实际电压与电池电量              *
 ************************************/
inline void VolGet(double V){
  SendData.Voltage = -3.3126889904968743e-18*V*V*V*V*V*V*V  \
                     +1.623217605075953e-14*V*V*V*V*V*V     \
                     -3.3719331192434486e-11*V*V*V*V*V      \
                     +3.847999653156838e-8*V*V*V*V          \
                     -0.00002604499123955503*V*V*V          \
                     +0.010452452154782833*V*V              \
                     -2.3016342267679173*V                  \
                     +214.85012707853883;
  SendData.Voltage *= 5;
  SendData.BatteryLevel = 100*(SendData.Voltage-3)/1.2;
}

/******************
 *计算土壤湿度     *
 *使用了滤波算法   *
 *NumRead-采样数量*
 *****************/
inline double SoilMoistGet(){
  int sum=0;
  for(int i=0;i<NumRead;i++){
    sum+=MoistRead[i];
  }
  //返回湿度(百分数)
  double ave=sum/NumRead;
  double per=(1-((ave-1400)/900.0))*100;
  return per;
}

//初始化土壤湿度数据
inline void InitMoist(){
  for(int i=0;i<NumRead;i++){
    MoistRead[i]=analogRead(SoilMoisturePin);
    delay(5);
  }
  return;
}

/*调试代码(输出数据,检测数据发送是否成功.etc)*/
inline void Test(esp_err_t *result){
  /*检测数据发送是否成功*/
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  /*打印数据*/
  Serial.print("土壤湿度:");
  Serial.println(SendData.SoilMoisture);
  Serial.print("电池电压:");
  Serial.println(SendData.Voltage);
  Serial.print("电池电量:");
  Serial.println(SendData.BatteryLevel);
  Serial.print("水泵状态:");
  Serial.println(ReceiveData.Bump.State);
}

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
  //开启串口
  Serial.begin(115200);

  //开启端口
  pinMode(BumpPin,OUTPUT);
  pinMode(SoilMoisturePin,INPUT);
  pinMode(VoltagePin,INPUT);

  //espnow,start!!!!!
  EspNowConnect();

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

  //初始化土壤湿度数据
  InitMoist();

  //将灌溉时间初始化为3s
  ReceiveData.Bump.Time=3000;
}

void Task0code(void * pvParameters){
  //读取电池电压数据并处理
  double V=analogRead(VoltagePin);
  VolGet(V);

  //读取土壤湿度数据并处理
  MoistRead[++Point]=analogRead(SoilMoisturePin);
  Point%=5;
  SendData.SoilMoisture=SoilMoistGet();

  //发送数据(每0.5秒发送一次)
  esp_err_t result = esp_now_send(ReceiverAddress, (uint8_t *) &SendData, sizeof(SendData));
  delay(500);

  //调试端口(默认关闭)
  // Test(&result);
}

void loop() {
  switch(ReceiveData.Bump.State){
  /*由单片机控制水泵*/
  case 0:
      //土壤较为干旱情况
      if(SendData.SoilMoisture<20){
        digitalWrite(BumpPin,HIGH);
        TimeStamp=millis();
        while(millis()-TimeStamp<ReceiveData.Bump.Time);
        digitalWrite(BumpPin,LOW);
      }
      //土壤非常干旱情况
      else if(SendData.SoilMoisture<50){
        ReceiveData.Bump.Time=5000;
        digitalWrite(BumpPin,HIGH);
        TimeStamp=millis();
        while(millis()-TimeStamp<ReceiveData.Bump.Time);
        digitalWrite(BumpPin,LOW);
        ReceiveData.Bump.Time=3000;
      }
      TimeStamp=0;
    break;
  /*手动控制水泵*/
  case 1:
      //比对数据并决定是否更改水泵状态
      if(ReceiveData.Bump.Switch!=cmp){
        cmp=ReceiveData.Bump.Switch;
        if(cmp){
          digitalWrite(BumpPin,HIGH);
        }
        else{
          digitalWrite(BumpPin,LOW);
        }
      }
    break;
  /*计划灌溉*/
  case 2:
      //计算时间戳并决定是否浇水
      if(!TimeStamp){
        TimeStamp=millis();
      }
      if(millis()-TimeStamp>ReceiveData.Bump.Interval){
        TimeStamp=millis();
        digitalWrite(BumpPin,HIGH);
        while(millis()-TimeStamp<ReceiveData.Bump.Time);
        digitalWrite(BumpPin,LOW);
        TimeStamp=millis();
      }
    break;
  }
}