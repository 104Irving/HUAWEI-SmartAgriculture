/*************************
 *3区-ESP32              *
 *室外温湿度、降雨、气压   *
 *愿意和我一辈子搞嵌入式吗?*
 *************************/
//降雨传感器待完成
#include <Wire.h>
#include <WiFi.h>
#include <BMP280.h>
#include <esp_now.h>
#include <Adafruit_AHTX0.h>

//初始化I2C引脚-第一个设备
#define SDA_PIN_1 21
#define SCL_PIN_1 22
/**初始化I2C引脚-第二个设备
 * #define SDA_PIN_2 15
 * #define SCL_PIN_2 4
 *(不知道会不会用到,先留着)
 **/

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

/*调试代码(输出数据,检测数据发送是否成功.etc)*/
void Test(esp_err_t result){
  /*检测数据发送是否成功*/
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  /*打印数据*/
  Serial.print("温度:");
  Serial.println(SendData.Temperature);
  Serial.print("湿度:");
  Serial.println(SendData.AirHumidity);
  Serial.print("降雨:");
  Serial.println(SendData.Rain);
  Serial.print("气压:");
  Serial.println(SendData.AtmoPre);
}

void setup() {
  //初始化串口
  Serial.begin(115200);

  //初始化I2C总线
  // Wire.begin(SDA_PIN_2, SCL_PIN_2);
  Wire.begin(SDA_PIN_1, SCL_PIN_1);
  /*意义不明的代码(待确认)
   *Wire.beigin;
   **/
 
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
  //读取气压&空气温湿度
  uint32_t Pressure = bmp280.getPressure();
  sensors_event_t Humidity, Temp;
  aht.getEvent(&Humidity, &Temp);
  SendData.AtmoPre=Pressure/1000;
  SendData.Temperature=Temp.temperature;
  SendData.AirHumidity=Humidity.relative_humidity;

  //发送数据
  esp_err_t result = esp_now_send(ReceiverAddress, (uint8_t *) &SendData, sizeof(SendData));
  delay(1000);

  //调试端口(默认关闭)
  // Test(result);
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
