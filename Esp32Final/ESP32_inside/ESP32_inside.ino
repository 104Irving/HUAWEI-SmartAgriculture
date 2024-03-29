/*************************
 *室内1区                *
 *温湿度、光强、水箱水位  *
 *水泵、风扇、天窗、LED   *
 *阴暗地爬行             *
 ************************/
#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>

/***************************
 *将ADDR模式设置为GND模式   *
 *ADDR引脚接地             *
 *其中地址为0010011(0x23)  *
 *若引脚接VCC              *
 *其中地址为1101100(0x5B)  *
 **************************/
#define ADDRESS_BH1750FVI 0x23  
#define ONE_TIME_H_RESOLUTION_MODE 0x20

//espnow传输数据结构体
typedef struct EspNowDataSend{
  int LightIntensity;          //光强
  int Temperature;             //温度
  int AirHumidity;             //湿度
  int WaterTank;               //水箱水位
} EspNowDataSend;
EspNowDataSend SendData;

//espnow接收数据结构体
typedef struct EspNowDataReceive{
  struct bump{
    int State;                   //水泵操作模式 0->由单片机自主控制;1->手动控制;2->计划
    int Switch;                  //水泵开关(仅手动控制状态使用) 0->关闭;1->开启
    int Time;                    //单次灌溉时长
    int Interval;                //计划操作时,间隔时间(单位:ms)
  };
  struct fan{
    int State;                   //风扇操作模式 0->由单片机自主控制;1—>手动控制;2->计划
    int Switch;                  //风扇开关(仅手动控制状态使用) 0->关闭;1—>开启
    int Time;                    //单次开启时长
    int Interval;                //计划操作时,间隔时间(单位:ms)
  };
  struct led{
    int State;                   //LED操作模式 0->由单片机自主控制;1->手动控制;2->计划
    int Switch;                  //LED开关(仅手动控制状态使用) 0->关闭;1->开启
    int Time;                    //单次开启时长
    int Interval;                //计划操作时,间隔时间(单位:ms)               
  };
  struct window{
    int State;                   //天窗操作模式 1->由单片机自主控制;1->手动控制;2->计划
    int Switch;                  //天窗开关(仅手动控制状态使用) 0->关闭;1->开启
    int Time;                    //单次开启时长
    int Interval;                //计划操作时,间隔时间(单位:ms)
  };
  bump Bump;
  fan Fan;
  led LED;
  window Window;
} EspNowDataReceive;
EspNowDataReceive ReceiveData;

//接收设备的MAC地址
uint8_t ReceiverAddress[] = {0x08, 0xD1, 0xF9, 0xE7, 0x2C, 0xE0};

//数据接收回调函数
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&ReceiveData, incomingData, sizeof(ReceiveData));
}

//I2C高低位数据位
byte HighByte = 0;
byte LowByte = 0;

/*调试代码(输出数据,检测数据发送是否成功.etc)*/
//控制的设备状态待添加
inline void Test(esp_err_t *result){
  /*检测数据发送是否成功*/
  if (*result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
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

  //初始化I2C
  Wire.begin();

  //espnow,start!!!!!
  EspNowConnect();
}

void loop() {
  //设置GY-30为单次L分辨率模式
  Wire.beginTransmission(ADDRESS_BH1750FVI);
  Wire.write(ONE_TIME_H_RESOLUTION_MODE);
  Wire.endTransmission();
  delay(150);

  //读取I2C总线传输的数据并处理(光强数据)
  Wire.requestFrom(ADDRESS_BH1750FVI,2);
  HighByte = Wire.read();
  LowByte = Wire.read();
  SendData.LightIntensity=(HighByte<<8)|LowByte;
  SendData.LightIntensity/=1.2;

  //发送数据(每0.5秒发送一次)
  esp_err_t result = esp_now_send(ReceiverAddress, (uint8_t *) &SendData, sizeof(SendData));
  delay(500);

  //调试端口(默认关闭)
  Test(&result);
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