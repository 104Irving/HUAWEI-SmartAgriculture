/***********************************
 *室内1区                          *
 *温湿度、光强、水箱水位、培养槽水位  *
 *水泵、风扇、天窗、LED              *
 *我想吃掉你的胰脏                   *
 ************************************/
#include <Wire.h>
#include <WiFi.h>
#include <SimpleDHT.h>
#include <ESP32Servo.h>
#include <PubSubClient.h>

/***************************
 *将ADDR模式设置为GND模式   *
 *ADDR引脚接地             *
 *其中地址为0010011(0x23)  *
 *若引脚接VCC              *
 *其中地址为1101100(0x5B)  *
 **************************/
#define ADDRESS_BH1750FVI 0x23  
#define ONE_TIME_H_RESOLUTION_MODE 0x20

//任务〇(控制)
TaskHandle_t Task0;

//MQTT传输数据结构体
typedef struct MQTT_DataSend{
  int LightIntensity;          //光强
  int Temperature;             //温度
  int AirHumidity;             //湿度
  int WaterTank;               //水箱水位 目前仅有三档(无法显示详细水位)-0:低水位;1:中水位;2:高水位
  int Flume;                   //培养槽水位 目前仅有三档(无法显示详细水位)-0:低水位;1:中水位;2:高水位
} MQTT_DataSend;
MQTT_DataSend SendData;

//MQTT接收数据结构体
typedef struct MQTT_Receive{
  struct bump{
    int State;                   //水泵操作模式 0->由单片机自主控制;1->手动控制;2->计划
    int Switch;                  //水泵开关(仅手动控制状态使用) 0->关闭;1->开启
    int Time;                    //单次灌溉时长
    unsigned long long Interval; //计划操作时,间隔时间(单位:ms)
    unsigned long long StartTime;//第一次启动前时间差
  };
  struct led{
    int State;                   //LED操作模式 0->基于光强进行控制;1->手动控制
    int Switch;                  //LED开关(仅手动控制状态使用) 0->关闭;1->开启
    int Condition;               //设定的开启标准(低于该值时开启)
  };
  struct fan{
    int State;                   //风扇操作模式 0->基于温度进行控制;1—>手动控制
    int Switch;                  //风扇开关(仅手动控制状态使用) 0->关闭;1—>开启
    int Temperature;             //设定的开启标准(高于此值时开启)
  };
  struct window{
    int State;                   //天窗操作模式 1->基于温度进行控制;1->手动控制
    int Switch;                  //天窗开关(仅手动控制状态使用) 0->关闭;1->开启
    int Temperature;             //设定的开启标准(高于此值时开启)
  };
  bump Bump;
  led LED;
  window Window;
  fan Fan;
} MQTT_Receive;
MQTT_Receive ReceiveData;

//WiFi
const char *ssid="Gino";
const char *password="20050601";

//MQTT Broker
const char *mqtt_broker="broker-cn.emqx.io";                  //IP地址
const int mqtt_port=1883;                                     //端口
const char Topic[19][40]={"Data/Inside/LightIntensity",       //0:光强
                          "Data/Inside/Temperature",           //1:室内温度
                          "Data/Inside/AirHumidity",           //2:室内湿度
                          "Data/Inside/WaterTank",             //3:水箱水位
                          "Data/Inside/Flume",                 //4:培养槽水位
                          "Control/Inside/Bump/State",         //5:室内水泵控制模式
                          "Control/Inside/Bump/Switch",        //6:室内水泵开关
                          "Control/Inside/Bump/Time",          //7:室内水泵单次灌溉时长
                          "Control/Inside/Bump/Interval",      //8:室内水泵灌溉间隔
                          "Control/Inside/Bump/StartTime",     //9:室内水泵第一次开启时间
                          "Control/Inside/LED/State",          //10:室内LED控制模式
                          "Control/Inside/LED/Switch",         //11:室内LED开关
                          "Control/Inside/LED/Condition",      //12:室内LED开启条件
                          "Control/Inside/Window/State",       //13:室内天窗控制模式
                          "Control/Inside/Window/Switch",      //14:室内天窗开关
                          "Control/Inside/Window/Temperature", //15:室内天窗开启条件
                          "Control/Inside/Fan/State",          //16:室内风扇控制模式
                          "Control/Inside/Fan/Switch",         //17:室内风扇开关
                          "Control/Inside/Fan/Temperature"};   //18:室内风扇开启条件
const char *mqtt_username="ESP32_02";                         //用户名
const char *mqtt_password="a12345678";                        //密码
char Buff[50];                                                //发送的消息

//声明MQTT客户端对象
WiFiClient espClient;
PubSubClient client(espClient);

//I/O端口
const int DHT_Pin=11;          //DHT传感器针脚
const int FlumePin=19;         //培养槽水位传感器针脚
const int TankPin=41;          //水箱水位传感器
const int BumpPin=59;          //水泵针脚
const int LED_Pin=18;          //LED针脚
const int WindowPin=41;        //天窗控制(舵机) 175->OFF;70->ON
const int FanPin=0;            //风扇针脚

//声明DHT传感器对象
SimpleDHT11 dht11(DHT_Pin);

//声明舵机对象
Servo myServo;

//I2C高低位数据位
byte HighByte = 0;
byte LowByte = 0;

//温湿度变量
byte temperature = 0;
byte humidity = 0;

//水泵控制的相关变量
typedef struct bump{
  int cmp;
  unsigned long long TimeStamp;
  unsigned long long TimeStartInterval;
}bump;
bump Bump={3,0,-1};

//天窗(舵机)控制的相关变量(默认关闭)
typedef struct window{
  int AngleNow;                //舵机目前所处的角度
  int AngleSet;                //设定的角度
} window;
window Window={175,175};

//风扇控制的相关变量(默认关闭)
typedef struct fan{
  int Now;                     //风扇目前状态
  int Set;                     //设定的角度
} fan;
fan Fan={0,0};

/*调试代码(输出数据,检测数据发送是否成功.etc)*/
//控制的设备状态待添加
inline void Test(){
  /*打印数据*/
  Serial.print("湿度:");
  Serial.println(SendData.AirHumidity);
  Serial.print("温度:");
  Serial.println(SendData.Temperature);
  Serial.print("光强:");
  Serial.println(SendData.LightIntensity);
  Serial.print("水箱水位:");
  Serial.println(SendData.WaterTank);
}

//初始化端口
inline void Init(){
  pinMode(FlumePin,INPUT);     //水槽水位传感器
  pinMode(TankPin,INPUT);      //水箱水位传感器
  pinMode(BumpPin,OUTPUT);     //水泵端口
  pinMode(LED_Pin,OUTPUT);     //LED端口
  pinMode(FanPin,OUTPUT);      //风扇端口
  myServo.attach(WindowPin);   //天窗端口(舵机)
  myServo.write(175);          //将天窗关闭
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
  for(int i=5;i<=18;i++){
    client.subscribe(Topic[i]);
  }
}

void setup() {
  //开启串口  
  Serial.begin(115200);

  //初始化端口
  Init();

  //初始化I2C
  Wire.begin();

  //连接MQTT
  MQTT_Init();

  //使用核心0, 控制
  xTaskCreatePinnedToCore(
                    Task0code,   /* Task function. */
                    "Task0",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task0,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(100);

  //将培养槽放水时间初始化为5s
  ReceiveData.Bump.Time=5000;
}

//处理接收到的订阅更新
void callback(char *topic, byte *payload, unsigned int length){
  int p=0;
  //水泵控制模式
  if(!strcmp(topic,Topic[5])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.Bump.State=(char)payload[p]-48;
  }
  //水泵开关
  else if(!strcmp(topic,Topic[6])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.Bump.Switch=(char)payload[p]-48;
  }
  //水泵单次灌溉时长
  else if(!strcmp(topic,Topic[7])){
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
  else if(!strcmp(topic,Topic[8])){
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
  else if(!strcmp(topic,Topic[9])){
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
  //LED控制模式
  else if(!strcmp(topic,Topic[10])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.LED.State=(char)payload[p]-48;
  }
  //LED开关
  else if(!strcmp(topic,Topic[11])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.LED.Switch=(char)payload[p]-48;
  }
  //LED开启条件
  else if(!strcmp(topic,Topic[12])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    int temp=0;
    while((char)payload[p]>='0'&&(char)payload[p]<='9'){
      temp*=10;
      temp+=((char)payload[p++]-48);
    }
    ReceiveData.LED.Condition=temp;
  }
  //天窗控制模式
  else if(!strcmp(topic,Topic[13])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.Window.State=(char)payload[p]-48;
  }
  //天窗开关
  else if(!strcmp(topic,Topic[14])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.Window.Switch=(char)payload[p]-48;
  }
  //天窗开启条件
  else if(!strcmp(topic,Topic[15])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    int temp=0;
    while((char)payload[p]>='0'&&(char)payload[p]<='9'){
      temp*=10;
      temp+=((char)payload[p++]-48);
    }
    ReceiveData.Window.Temperature=temp;
  }
  //风扇控制模式
  else if(!strcmp(topic,Topic[16])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.Fan.State=(char)payload[p]-48;
  }
  //风扇开关
  else if(!strcmp(topic,Topic[17])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    ReceiveData.Fan.Switch=(char)payload[p]-48;
  }
  //风扇开启条件
  else if(!strcmp(topic,Topic[18])){
    while((char)payload[p]<'0'||(char)payload[p]>'9'){
      p++;
    }
    int temp=0;
    while((char)payload[p]>='0'&&(char)payload[p]<='9'){
      temp*=10;
      temp+=((char)payload[p++]-48);
    }
    ReceiveData.Fan.Temperature=temp;
  }
}

//发送数据
inline void DataPublish(){
  //光强
  sprintf(Buff,"LightIntensity:%d",SendData.LightIntensity);
  client.publish(Topic[0],Buff);

  //室内温度
  sprintf(Buff,"Temperature:%lf",SendData.Temperature);
  client.publish(Topic[1],Buff);

  //室内湿度
  sprintf(Buff,"AirHumidity:%d",SendData.AirHumidity);
  client.publish(Topic[2],Buff);

  //水箱水位
  sprintf(Buff,"WaterTank:%d",SendData.WaterTank);
  client.publish(Topic[3],Buff);

  //培养槽水位
  sprintf(Buff,"Flume:%d",SendData.Flume);
  client.publish(Topic[4],Buff);
}

//控制部分
void Task0code(void * pvParameters){
  //如果水箱水位为低水位,则停止灌溉
  if(!SendData.WaterTank){
    goto NextModule;
  }

/*水泵控制*/
  switch(ReceiveData.Bump.State){
  /*由单片机控制水泵*/
  case 0:
      //培养槽水量较少
      if(SendData.Flume==0){
        digitalWrite(BumpPin,HIGH);
        Bump.TimeStamp=millis();
        while(millis()-Bump.TimeStamp<ReceiveData.Bump.Time);
        digitalWrite(BumpPin,LOW);
      }
      //培养槽极其缺水
      else if(SendData.Flume<50){
        ReceiveData.Bump.Time=8000;
        digitalWrite(BumpPin,HIGH);
        Bump.TimeStamp=millis();
        while(millis()-Bump.TimeStamp<ReceiveData.Bump.Time);
        digitalWrite(BumpPin,LOW);
        ReceiveData.Bump.Time=5000;
      }
      Bump.cmp=3;
      Bump.TimeStamp=0;
    break;
  /*手动控制水泵*/
  case 1:
      //比对数据并决定是否更改水泵状态
      if(ReceiveData.Bump.Switch!=Bump.cmp){
        Bump.cmp=ReceiveData.Bump.Switch;
        if(Bump.cmp){
          digitalWrite(BumpPin,HIGH);
        }
        else{
          digitalWrite(BumpPin,LOW);
        }
      }
      Bump.TimeStamp=0;
    break;
  /*计划灌溉*/
  case 2:
      //计算时间戳并决定是否浇水
      if(!Bump.TimeStamp){
        Bump.TimeStamp=millis();
        Bump.TimeStartInterval=ReceiveData.Bump.StartTime;
      }
      if(Bump.TimeStartInterval){
        if(millis()-Bump.TimeStamp>Bump.TimeStartInterval){
          Bump.TimeStamp=millis();
          digitalWrite(BumpPin,HIGH);
          while(millis()-Bump.TimeStamp<ReceiveData.Bump.Time);
          digitalWrite(BumpPin,LOW);
          Bump.TimeStamp=millis();
          Bump.TimeStartInterval=0;
        }
        else break;
      }
      if(millis()-Bump.TimeStamp>ReceiveData.Bump.Interval){
        Bump.TimeStamp=millis();
        digitalWrite(BumpPin,HIGH);
        while(millis()-Bump.TimeStamp<ReceiveData.Bump.Time);
        digitalWrite(BumpPin,LOW);
        Bump.TimeStamp=millis();
      }
      Bump.cmp=3;
    break;
  }

NextModule:
/*LED控制*/
  switch(ReceiveData.LED.State){
  /*基于光强开启*/
  case 0:
    //光强低于设定值时开启LED
    if(SendData.LightIntensity<ReceiveData.LED.Condition){
      digitalWrite(LED_Pin,HIGH);
    }
    else{
      digitalWrite(LED_Pin,LOW);
    }
    delay(10);
    break;
  /*手动控制*/  
  case 1:
    if(ReceiveData.LED.Switch){
      digitalWrite(LED_Pin,HIGH);
    }
    else{
      digitalWrite(LED_Pin,LOW);
    }
    delay(10);
    break;
  }

/*天窗(舵机)控制*/
  switch(ReceiveData.Window.State){
  /*基于温度开启*/
  case 0:
    //不低于设定温度时开启
    if(SendData.Temperature>=ReceiveData.Window.Temperature){
      Window.AngleSet=70;
      if(Window.AngleNow>Window.AngleSet){
        Window.AngleNow--;
        myServo.write(Window.AngleNow);
      }
    }
    else{
      Window.AngleSet=175;
      if(Window.AngleNow<Window.AngleSet){
        Window.AngleNow++;
        myServo.write(Window.AngleNow);
      }
    }
    break;
  /*手动控制*/
  case 1:
    //天窗开
    if(ReceiveData.Window.Switch){
      Window.AngleSet=70;
      if(Window.AngleNow>Window.AngleSet){
        Window.AngleNow--;
        myServo.write(Window.AngleNow);
      }
    }
    //天窗关
    else{
      Window.AngleSet=175;
      if(Window.AngleNow<Window.AngleSet){
        Window.AngleNow++;
        myServo.write(Window.AngleNow);
      }
    }
    break;
  }

/*风扇控制*/
  switch(ReceiveData.Fan.State){
  /*基于温度开启*/
  case 0:
    //不低于设定温度时开启
    if(SendData.Temperature>=ReceiveData.Fan.Temperature){
      Fan.Set=1;
      if(Fan.Set!=Fan.Now){
        Fan.Now=1;
        digitalWrite(FanPin,HIGH);
      }
    }
    else{
      Fan.Set=0;
      if(Fan.Set!=Fan.Now){
        Fan.Now=0;
        digitalWrite(FanPin,LOW);
      }
    }
    break;
  /*手动控制*/
  case 1:
    //风扇开
    if(ReceiveData.Fan.Switch){
      digitalWrite(FanPin,HIGH);
    }
    else{
      digitalWrite(FanPin,LOW);
    }
    break;
  }
}

//传感器读数
void loop() {
  //设置GY-30为单次L分辨率模式
  Wire.beginTransmission(ADDRESS_BH1750FVI);
  Wire.write(ONE_TIME_H_RESOLUTION_MODE);
  Wire.endTransmission();
  delay(180);

  //读取I2C总线传输的数据并处理(光强数据)
  Wire.requestFrom(ADDRESS_BH1750FVI,2);
  HighByte = Wire.read();
  LowByte = Wire.read();
  SendData.LightIntensity=(HighByte<<8)|LowByte;
  SendData.LightIntensity/=1.2;

  //读取温湿度数据
  dht11.read(&temperature, &humidity, NULL);
  SendData.Temperature=temperature;
  SendData.AirHumidity=humidity;

  //读取水箱及培养槽水位
  int temp=analogRead(FlumePin);
  if(temp>3000){
    /*高水位*/
    SendData.Flume=2;
  }
  else if(temp<2300){
    /*低水位*/
    SendData.Flume=0;
  }
  else{
    /*中水位*/
    SendData.Flume=1;
  }
  temp=analogRead(TankPin);
  if(temp>3000){
    /*高水位*/
    SendData.WaterTank=2;
  }
  else if(temp<2300){
    /*低水位*/
    SendData.WaterTank=0;
  }
  else{
    /*中水位*/
    SendData.WaterTank=1;
  }

  //发布与订阅消息
  DataPublish();
  client.loop();

  //调试端口(默认关闭)
  // Test();
}

/*附GY-30指令集合***************************************************************************************
 *           断电           *0000_0000*无激活状态                                                      *
 ******************************************************************************************************
 *           通电           *0000_0001*等待测量指令                                                    *
 ******************************************************************************************************
 *           重置           *0000_0111*重置数字寄存器值,重置指令在断电模式下不起作用                      *
 ******************************************************************************************************
 *连续H(ADDR->VCC)分辨率模式 *0001_0000*在11x分辨率下开始测量,测量时间一般为120ms                         *
 ******************************************************************************************************
 *连续H(ADDR->VCC)分辨率模式 *0001_0001*在0.51x分辨率开始测量,测量时间一般为120ms                         *
 ******************************************************************************************************
 *连续L(ADDR->GND)分辨率模式 *0001_0011*在411x分辨率下开始测量,测试时间一般为16ms                         *
 ******************************************************************************************************
 *一次H(ADDR->VCC)分辨率模式 *0010_0000*在11x分辨率下开始测量,测试时间一般为120ms,测试后自动设置为断电模式  *
 ******************************************************************************************************
 *一次H(ADDR->VCC)分辨率模式2*0010_0001*在0.51x分辨率下开始测量,测试时间一般为120ms,测试后自动设置为断电模式*
 ******************************************************************************************************
 *一次L(ADDR->GND)分辨率模式 *0010_0011*在411x分辨率下开始测量,测试时间一般为16ms,测试后自动设置为断电模式  *
 ******************************************************************************************************/