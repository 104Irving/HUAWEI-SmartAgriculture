float volr = 0;  //读取的电压原始值
float vol = 0;  //计算的电压值
int battery = 0;
int analogPin = 34;  //1号ADC引脚

void setup(){

  Serial.begin(115200);

}

void loop(){
  float x = analogRead(analogPin);
  //volr = map(volr, 0, 880, 0 ,4095);
  vol = -3.3126889904968743e-18*x*x*x*x*x*x*x+1.623217605075953e-14*x*x*x*x*x*x-3.3719331192434486e-11*x*x*x*x*x+3.847999653156838e-8*x*x*x*x-0.00002604499123955503*x*x*x+0.010452452154782833*x*x-2.3016342267679173*x+214.85012707853883;
  vol = vol*5;  //计算电压；
  battery = 100*(vol - 2.5)/1.7;  //计算电量
  
  Serial.print("电压：");
  Serial.print(vol);
  Serial.println("v");
  Serial.println(volr);
  Serial.print("电量：");
  Serial.print(battery);
  Serial.println("％");
  delay(500);

}