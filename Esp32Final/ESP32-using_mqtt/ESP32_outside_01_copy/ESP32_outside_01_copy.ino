/*************************************
 *3区-ESP32                          *
 *室外温湿度、降雨、气压、电池电压与电量*
 *愿意和我一辈子搞嵌入式吗?            *
 *************************************/
#include <Wire.h>
#include <WiFi.h>
#include <BMP280.h>
#include <PubSubClient.h>
#include <Adafruit_AHTX0.h>

//初始化I2C引脚-第一个设备
#define SDA_PIN_1 21
#define SCL_PIN_1 22
/**初始化I2C引脚-第二个设备
 * #define SDA_PIN_2 15
 * #define SCL_PIN_2 4
 *(不知道会不会用到,先留着)
 **/

//MQTT传输数据结构体
typedef struct MQTT_DataSend{
  int Temperature;    //温度
  int AirHumidity;    //空气湿度
  int Rain;           //降雨
  int AtomPre;        //气压
  double Voltage;     //电池电压
  int BatteryLevel;   //电池电量
} MQTT_DataSend;
MQTT_DataSend SendData;

//WiFi
const char *ssid="Gino";
const char *password="20050601";

//MQTT Broker
const char *mqtt_broker = "broker-cn.emqx.io";        //IP地址
const int mqtt_port=1883;                             //端口
const char Topic[6][40]={"Data/Outside/Temperature",  //0:室外温度
                         "Data/Outside/AirHumidity",  //1:室外空气湿度
                         "Data/Outside/Rain",         //2:降雨
                         "Data/Outside/AtomPre",      //3:气压
                         "Data/Outside/Voltage",      //4:电池电压
                         "Data/Outside/BatteryLevel"};//5:电池电量
const char *mqtt_username="ESP32_01";                 //用户名
const char *mqtt_password="a12345678";                //密码
char Buff[50];                                        //发送的消息

//声明MQTT客户端对象
WiFiClient espClient;
PubSubClient client(espClient);

//声明Aht20&Bmp20
Adafruit_AHTX0 aht;
BMP280 bmp280;

//定义端口
const int RainPin=4;           //降雨传感器
const int VoltagePin=34;       //电池电压针脚

//设置降雨传感器采样数量
const int NumRead=5;           //采样数量
int RainRead[NumRead];         //存储样本
int Point=0;                   //指示目前最新数据

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

//初始化降雨传感器数据
void InitRain(){
  for(int i=0;i<NumRead;i++){
    RainRead[i]=analogRead(RainPin);
    delay(5);
  }
  return;
}

//读取降雨传感器数据
double RainGet(){
  int sum=0;
  for(int i=0;i<NumRead;i++){
    sum+=RainRead[i];
  }
  //返回降雨值(百分数)
  double ave=sum/NumRead;
  double per=(1-((ave-900)/1300.0))*100;
  return per;
}

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
  /**由于此处仅做发送,故没有写回调函数
   *client.setCallback(callback);
  **/
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
}

//端口初始化
inline void Connect(){
  //初始化雨水传感器
  pinMode(RainPin,INPUT);
  //初始化电压读取端口
  pinMode(VoltagePin,INPUT);
}

//发送数据
inline void DataPublish(){
  //室外温度
  sprintf(Buff,"Temperature:%d",SendData.Temperature);
  client.publish(Topic[0],Buff);

  //室外空气湿度
  sprintf(Buff,"AirHumidity:%d",SendData.AirHumidity);
  client.publish(Topic[1],Buff);

  //降雨
  sprintf(Buff,"Rain:%d",SendData.Rain);
  client.publish(Topic[2],Buff);

  //气压
  sprintf(Buff,"AtomPre:%d",SendData.AtomPre);
  client.publish(Topic[3],Buff);

  //电池电压
  sprintf(Buff,"Voltage:%lf",SendData.Voltage);
  client.publish(Topic[4],Buff);

  //电池电量
  sprintf(Buff,"BatteryLevel:%lf",SendData.BatteryLevel);
  client.publish(Topic[5],Buff);
}

/*调试代码(输出数据,检测数据发送是否成功.etc)*/
inline void Test(){
  /*打印数据*/
  Serial.print("温度:");
  Serial.println(SendData.Temperature);
  Serial.print("湿度:");
  Serial.println(SendData.AirHumidity);
  Serial.print("降雨:");
  Serial.println(SendData.Rain);
  Serial.print("气压:");
  Serial.println(SendData.AtomPre);
  Serial.print("电池电压:");
  Serial.println(SendData.Voltage);
  Serial.print("电池电量:");
  Serial.println(SendData.BatteryLevel);
}

void setup() {
  //初始化串口
  Serial.begin(115200);

  //连接MQTT
  MQTT_Init();

  //初始化I2C总线
  // Wire.begin(SDA_PIN_2, SCL_PIN_2);
  Wire.begin(SDA_PIN_1, SCL_PIN_1);
  /**意义不明的代码(待确认)
   *Wire.beigin;
  **/

  //初始化Aht20&Bmp280
  Detect();

  //初始化引脚
  Connect();

  //初始化雨水数据
  InitRain();
}

void loop() {
  //读取气压&空气温湿度
  uint32_t Pressure = bmp280.getPressure();
  sensors_event_t Humidity, Temp;
  aht.getEvent(&Humidity, &Temp);
  SendData.AtomPre=Pressure/1000;
  SendData.Temperature=Temp.temperature;
  SendData.AirHumidity=Humidity.relative_humidity;

  //读取雨水传感器数值
  RainRead[++Point]=analogRead(RainPin);
  Point%=NumRead;
  SendData.Rain=RainGet();

  //读取电池电压数据并处理
  double V=analogRead(VoltagePin);
  VolGet(V);

  //发布数据
  DataPublish();

  //调试端口(默认关闭)
  // Test();
}