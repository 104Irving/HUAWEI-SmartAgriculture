 /*
 * POST Data 1.1
 * 
 */

 /************TCP**********************************/
#include <WiFi.h>
const char *ssid = "test";//WIFI
const char *password = "12345678";//WIFI密码
const char* serverIP = "183.230.40.33"; //欲访问的地址
uint16_t serverPort = 80;         //服务器端口号
String url = "http://api.heclouds.com/devices/526038005/datapoints?type=3";//网址 设备ID
String api="NkjCsVzErzqKLv8pKlWMIG6e8DE=";//api-key
String post;//http请求
int Content_Length;
WiFiClient client; //声明一个客户端对象，用于与服务器进行连接
/****************************************************/


/************数据采集*********************************/
size_t data_get[5][8]={//指令      id
  {1,3,0,1,0,2,149,203},//TDS值    1
  {2,3,0,8,0,1,5,251},//土壤ph值    2
  {3,3,0,0,0,6,196,42},//温湿度     3
  {4,3,0,5,0,1,148,94},//CO2       4
  {5,3,0,7,0,2,116,78}//光照        5
  };
//传感器数据
long tsd_value=0,co2_value=0,lig_value=0;
float ph_value=0,tem_value=0,hum_value=0;
String string1,string2,string3,string4;
int value = 0;
static unsigned long time_=0;//定义初始发送时间为0
static unsigned long time_out=0;//定义超时发送时间为0
/****************************************************/

void setup()
{
    Serial2.begin(9600);//初始化波特率9600 数据收发串口
    Serial.begin(9600);//                 调试打印串口
    Serial.println();
    
   ;
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);//连接到网络

    while (WiFi.status() != WL_CONNECTED) {//等待网络连接成功
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());//打印模块IP

}

void loop()
{
   //获取数组长度
   int len=sizeof(data_get)/sizeof(size_t);
   int len2=sizeof(data_get[0])/sizeof(size_t);
   int len_data=len/len2;

    if(millis()-time_>200){//当系统时间大于200ms 0.2s采集一个传感器数据
     for(int j=0;j<8;j++){
      Serial2.write(data_get[value][j]);//向传感器发送指令 
     }
      time_=millis();
    }
    
     
  
  
  if(Serial2.available()){
       value++;//累加 为下一条指令发送
       
       size_t counti = Serial2.available();//串口缓冲器 返回的是缓冲区准确的可读字节数
       uint8_t sbuf[counti];
       Serial2.readBytes(sbuf, counti);//从串口读取指定长度counti的字符到缓存数组sbuf。数组
//       Serial.write(sbuf,counti);
       delay(50);
       switch (sbuf[0]){//判断传感器ID
       case 1:string1=tohex(int(sbuf[3]));
              string2=tohex(int(sbuf[4]));
              tsd_value=todec(string1,string2);
              Serial.print("tds: ");
              Serial.println(tsd_value);
              break;
       case 2:string1=tohex(int(sbuf[3]));
              string2=tohex(int(sbuf[4]));
              ph_value=((float)todec(string1,string2))/10;
              Serial.print("ph: ");
              Serial.println(ph_value);
              break;
       case 3:string1=tohex(int(sbuf[3]));
              string2=tohex(int(sbuf[4]));
              hum_value=((float)todec(string1,string2))/10;
              string1=tohex(int(sbuf[5]));
              string2=tohex(int(sbuf[6]));
              tem_value=((float)todec(string1,string2))/10;
              Serial.print("tem: ");
              Serial.print(tem_value);
              Serial.print("  hum: ");
              Serial.println(hum_value);
              break;
       case 4:string1=tohex(int(sbuf[3]));
              string2=tohex(int(sbuf[4]));
              co2_value=((float)todec(string1,string2));
              Serial.print("CO2: ");
              Serial.println(co2_value);
              break;
       case 5:string1=tohex(int(sbuf[3]));
              string2=tohex(int(sbuf[4]));
              string3=tohex(int(sbuf[5]));
              string4=tohex(int(sbuf[6]));
              lig_value=((float)todec_lig(string1,string2,string3,string4));
              Serial.print("light: ");
              Serial.println(lig_value);
              break;
       }
       
  }

  if(millis()-time_out>4000){//采集超时处理
    value=5;
    time_out=millis();
  }
  if(value==len_data){//判断当指令均已发送后
    value=0;//置0  
    Serial.print("connecting to ");//打印连接服务器IP
    Serial.println(serverIP);

    // Use WiFiClient class to create TCP connections
    if (!client.connect(serverIP, serverPort)) {//判断是否连接服务器
        Serial.println("connection failed");
        return;
    }else{//连接成功
       Serial.println("connection succ");
       Serial.println();
       String data_value="{\"tem\":"+String(tem_value)+",\"hum\":"+String(hum_value)
          +",\"lig\":"+String(lig_value)+",\"tds\":"+String(tsd_value)
          +",\"CO2\":"+String(co2_value)+",\"soil_ph\":"+String(ph_value)
          +",\"ec\":"+String(tsd_value/0.47)+"}\r\n\r\n";
       Content_Length=data_value.length();
       post=String("POST ")+url+" HTTP/1.1\r\n"+"api-key: "+api+"\r\n"
          +"Host:api.heclouds.com\r\n"+"Connection:close\r\n"+"Content-Length:"
          +String(Content_Length)+"\r\n\r\n"+data_value;
//          +"{\"tem\":"+String(tem_value)+",\"hum\":"+String(hum_value)
//          +",\"lig\":"+String(lig_value)+",\"tds\":"+String(tsd_value)
//          +",\"CO2\":"+String(co2_value)+",\"soil_ph\":"+String(ph_value)
//          +"}\r\n\r\n";
      
          
          Serial.println(Content_Length);
           Serial.print(post);//串口打印HTTP请求
           client.print(post);//向服务器发送HTTP请求
   
      }
  }
  
  while(client.available()) {//判断WIFI是否有数据
        String line = client.readStringUntil('\r');//读取WIFI数据赋给line
        Serial.print(line);//打印line
          
    }
   
}

void init_data(){//初始化所有数据，当传感器未采集到数据时，值为0；
  tsd_value=0;
  ph_value=0;
  hum_value=0;
  tem_value=0;
  co2_value=0;
  lig_value=0;
}
 
//字符串合并，转为long数据  
long todec(String string1,String string2){ 
       String str=string1+string2;//合并两个字符串
       int str_len = str.length() + 1;//str字符串长度
       char char_array[str_len];//创建字符数组
       str.toCharArray(char_array, str_len);//将str转为char数组
       long iOut;
       iOut = strtol(char_array, NULL, 16);//将char_array数组以16为long权值 转为long数据
       return iOut;
}

//字符串合并（光照，转为long数据
long todec_lig(String string1,String string2,String string3,String string4){   
       String str=string1+string2+string3+string4;
       int str_len = str.length() + 1;
       char char_array[str_len];
       str.toCharArray(char_array, str_len);
       long iOut;
       iOut = strtol(char_array, NULL, 16);
       return iOut;
}


//十进制转十六进制
String tohex(int n) {
  if (n == 0) {
    return "00"; //n为0
  }
  String result = "";
  char _16[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
  };
  const int radix = 16;
  while (n) {
    int i = n % radix;          // 余数
    result = _16[i] + result;   // 将余数对应的十六进制数字加入结果
    n /= radix;                 // 除以16获得商，最为下一轮的被除数
  }
  if (result.length() < 2) {
    result = '0' + result; //不足两位补零
  }
  return result;
}

