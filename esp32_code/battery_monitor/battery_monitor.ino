float volr = 0;  //读取的电压原始值
float vol = 0;  //计算的电压值
int battery = 0;
int analogPin = 35;  //1号ADC引脚

void setup(){

  Serial.begin(115200);

}

void loop(){
  volr = analogRead(analogPin);
  vol = volr*5*3.3/4096;  //计算电压；
  battery = 100*(vol - 2.5)/1.7;  //计算电量
  
  Serial.print("电压：");
  Serial.print(vol);
  Serial.println("v");
  
  Serial.print("电量");
  Serial.print(battery);
  Serial.println("％");
  delay(1000);

}