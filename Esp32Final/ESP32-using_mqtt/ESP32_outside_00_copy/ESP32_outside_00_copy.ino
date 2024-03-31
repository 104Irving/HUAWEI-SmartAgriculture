/*******************
 *2区-ESP32        *
 *室外土壤湿度、电压 *
 *管理室外水泵      *
 *Ciallo :)        *
 *******************/
#include <WiFi.h>
#include <PubSubClient.h>

//任务〇(数据)
TaskHandle_t Task0;

//MQTT传输数据结构体
typedef struct MQTT_DataSend{
  int SoilMoisture;            //土壤湿度
  double Voltage;              //电池电压
  int BatteryLevel;            //电池电量
} MQTT_DataSend;
MQTT_DataSend SendData;

//MQTT接收数据结构体
typedef struct MQTT_Receive{
  struct bump{
    int State;                   //水泵操作模式 0->由单片机自主控制;1->手动控制;2->计划
    int Switch;                  //水泵开关 0->关闭;1->开启
    int Time;                    //单次灌溉时长,默认为3s
    unsigned long long Interval; //计划操作时,间隔时间(单位:ms)
    unsigned long long StartTime;//第一次启动前时间差
  };
  bump Bump;
  int WaterTank;                 //水箱水位
} MQTT_DataReceive;
MQTT_DataReceive ReceiveData;

//WiFi
const char *ssid="Gino";
const char *password="20050601";

//MQTT Broker
const char *mqtt_broker="broker-cn.emqx.io";                 //IP地址
const int mqtt_port=1883;                                      //端口
const char Topic[9][40]={"Data/Outside/SoilMoisture",          //0:土壤湿度
                         "Data/Outside/Voltage",               //1:电池电压
                         "Data/Outside/BatteryLevel",          //2:电池电量
                         "Control/Outside/Bump/State",         //3:室外水泵控制模式
                         "Control/Outside/Bump/Switch",        //4:室外水泵开关
                         "Control/Outside/Bump/Time",          //5:室外水泵单次灌溉时长
                         "Control/Outside/Bump/Interval",      //6:室外水泵灌溉间隔
                         "Control/Outside/Bump/StartTime",     //7:室外水泵第一次启动时间差
                         "Data/Inside/WaterTank"};             //8:水箱水位
const char *mqtt_username="ESP32_00";                          //用户名
const char *mqtt_password="a12345678";                         //密码
char Buff[50];                                                 //发送的消息

//声明MQTT客户端对象
WiFiClient espClient;
PubSubClient client(espClient);

//I/O端口
const int BumpPin=0;           //水泵针脚
const int SoilMoisturePin=35;  //土壤湿度传感器针脚
const int VoltagePin=34;       //电池电压针脚

//设置土壤湿度传感器采样数量
const int NumRead=5;           //采样数量
int MoistRead[NumRead];        //存储样本
int Point=0;                   //指示目前最新数据

//时间戳,用于控制灌溉时间及计算第一次开启时间差
unsigned long long TimeStamp=0;
unsigned long long TimeStartInterval=-1;

//比对以判断水泵状态是否改变
int cmp=3;

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

//MQTT相关配置
inline void MQTT_Init(){
  //连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");

  //连接MQTT Broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)){
      Serial.println("emqx mqtt broker connected");
    }
    else{
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  //订阅主题
  for(int i=3;i<=8;i++){
    client.subscribe(Topic[i]);
  }
}

//初始化土壤湿度数据
inline void InitMoist(){
  for(int i=0;i<NumRead;i++){
    MoistRead[i]=analogRead(SoilMoisturePin);
    delay(5);
  }
  return;
}

//开启端口
inline void Connect(){
  pinMode(BumpPin,OUTPUT);
  pinMode(SoilMoisturePin,INPUT);
  pinMode(VoltagePin,INPUT);
}

/*调试代码(输出数据,检测数据发送是否成功.etc)*/
inline void Test(){
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

void setup() {
  //开启串口
  Serial.begin(115200);

  //开启端口
  Connect();

  //连接MQTT
  MQTT_Init();

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

//处理接收到的订阅更新
void callback(char *topic, byte *payload, unsigned int length){
  int p=0;
  //水泵控制模式
  if(!strcmp(topic,Topic[3])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.Bump.State=(char)payload[p]-48;
  }
  //水泵开关
  else if(!strcmp(topic,Topic[4])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.Bump.Switch=(char)payload[p]-48;
  }
  //水泵单次灌溉时长
  else if(!strcmp(topic,Topic[5])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    int temp=0;
    while((char)payload[p]>='0'&&(char)payload[p]<='9'){
      temp*=10;
      temp+=((char)payload[p++]-48);
    }
    ReceiveData.Bump.Time=temp;
  }
  //水泵灌溉间隔
  else if(!strcmp(topic,Topic[6])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    unsigned long long temp=0;
    while((char)payload[p]>='0'&&(char)payload[p]<='9'){
      temp*=10;
      temp+=((char)payload[p++]-48);
    }
    ReceiveData.Bump.Interval=temp;
  }
  //水泵第一次启动间隔
  else if(!strcmp(topic,Topic[7])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    unsigned long long temp=0;
    while((char)payload[p]>='0'&&(char)payload[p]<='9'){
      temp*=10;
      temp+=((char)payload[p++]-48);
    }
    ReceiveData.Bump.StartTime=temp;
  }
  //水箱水位
  else if(!strcmp(topic,Topic[8])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.WaterTank=(char)payload[p]-48;
  }
}

//发送数据
inline void DataPublish(){
  //土壤湿度
  sprintf(Buff,"SoilMoisture:%d",SendData.SoilMoisture);
  client.publish(Topic[0],Buff);

  //室外空气湿度
  sprintf(Buff,"Voltage:%lf",SendData.Voltage);
  client.publish(Topic[1],Buff);

  //降雨
  sprintf(Buff,"BatteryLevel:%d",SendData.BatteryLevel);
  client.publish(Topic[2],Buff);
}

void Task0code(void * pvParameters){
  //读取电池电压数据并处理
  double V=analogRead(VoltagePin);
  VolGet(V);

  //读取土壤湿度数据并处理
  MoistRead[++Point]=analogRead(SoilMoisturePin);
  Point%=NumRead;
  SendData.SoilMoisture=SoilMoistGet();

  //发布与订阅消息
  DataPublish();
  client.loop();

  //调试端口(默认关闭)
  // Test();
}

void loop() {
  //如果水箱水位为"低水位",则停止浇灌
  if(!ReceiveData.WaterTank){
    return;
  }

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
      cmp=3;
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
      TimeStamp=0;
    break;
  /*计划灌溉*/
  case 2:
      //计算时间戳并决定是否浇水
      if(!TimeStamp){
        TimeStamp=millis();
        TimeStartInterval=ReceiveData.Bump.StartTime;
      }
      if(TimeStartInterval){
        if(millis()-TimeStamp>TimeStartInterval){
          TimeStamp=millis();
          digitalWrite(BumpPin,HIGH);
          while(millis()-TimeStamp<ReceiveData.Bump.Time);
          digitalWrite(BumpPin,LOW);
          TimeStamp=millis();
          TimeStartInterval=0;
        }
        else break;
      }
      if(millis()-TimeStamp>ReceiveData.Bump.Interval){
        TimeStamp=millis();
        digitalWrite(BumpPin,HIGH);
        while(millis()-TimeStamp<ReceiveData.Bump.Time);
        digitalWrite(BumpPin,LOW);
        TimeStamp=millis();
      }
      cmp=3;
    break;
  }
}