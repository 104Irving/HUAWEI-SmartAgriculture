/*************************
 *3区-ESP32              *
 *室外温湿度、降雨、气压   *
 *愿意和我一辈子搞嵌入式吗?*
 *************************/
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
} MQTT_DataSend;
MQTT_DataSend SendData;

//WiFi
const char *ssid="Gino";
const char *password="20050601";

//MQTT Broker
const char *mqtt_broker = "broker-cn.emqx.io";        //IP地址
const int mqtt_port=1883;                             //端口
const char Topic[4][40]={"Data/Outside/Temperature",  //0:室外温度
                         "Data/Outside/AirHumidity",  //1:室外空气湿度
                         "Data/Outside/Rain",         //2:降雨
                         "Data/Outside/AtomPre"};     //3:气压
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

//设置降雨传感器采样数量
const int NumRead=5;           //采样数量
int RainRead[NumRead];         //存储样本
int Point=0;                   //指示目前最新数据

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

  //发布数据
  DataPublish();

  //调试端口(默认关闭)
  // Test();
}