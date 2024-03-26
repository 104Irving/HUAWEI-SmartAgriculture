/********************************************************
 * 传感器-8
 * 有水   LOW     0
 * 无水   HIGH    1
 * 
 * 继电器-13
 * 低电平触发  LOW   0
 *
 *********************************************************/
 
int sensorpin = 8;//传感器引脚 有水为0；无水为1
int pumpin    = 13;//水泵引脚 低电平触发 digitalWrite（8，LOW）；
int var;
 
void setup() {
  Serial.begin(9600);
  
  pinMode(8,INPUT);
  pinMode(13,OUTPUT);
}
 
void loop() {
 
  var = digitalRead(8);
 
  //如果传感器检测值为1表示没水;0表示有水
  if(var==HIGH)
  {
    digitalWrite(pumpin,LOW);//水泵打开
   delay(3000);//浇水的时间是3秒
    digitalWrite(pumpin,HIGH);//水泵关闭
    }
    else
    {
    digitalWrite(pumpin,HIGH);//水泵关闭
 
   
    }
 
    Serial.print("var=");
    Serial.println(var);
    int var2=digitalRead(pumpin);
    Serial.print("var2=");
    Serial.println(var2);
 
    delay(10000);
    //delay(3600000);//一小时扫描一次
 
}
 
 