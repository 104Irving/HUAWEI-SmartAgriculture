float vol = 0;  //计算的电压值
int Filter_Value = 0;

int x = 0;
int battery = 0;
int analogPin = 34;  //1号ADC引脚

/*
float a = 0;
float b = 0;
float c = 0;
*/

int Value = analogRead(analogPin)+8;

void setup(){

  Serial.begin(115200);

}

void loop(){
  Filter_Value = Filter();
  Value = Filter_Value;
  x = Filter_Value;
  //x = analogRead(analogPin);  //读取电压ADC原始值

  if((x-880)<5||(880-x)<5)
  x = 880;
  //满电补偿

  vol = -3.3126889904968743e-18*x*x*x*x*x*x*x+1.623217605075953e-14*x*x*x*x*x*x-3.3719331192434486e-11*x*x*x*x*x+3.847999653156838e-8*x*x*x*x-0.00002604499123955503*x*x*x+0.010452452154782833*x*x-2.3016342267679173*x+214.85012707853883;
  //拟合曲线校正ADC
  vol = vol*5;  //计算电压；
  battery = 100*(vol - 3)/1.2;  //计算电量

/*
  a = vol;
  delay(250);
  c = vol;
  delay(250);
  b = vol;
  vol = (a+b+c)/3;
  //减小波动
*/
  
  Serial.print("电压：");
  Serial.print(vol);
  Serial.println("v");
  //Serial.println(x);
  Serial.print("电量：");
  Serial.print(battery);
  Serial.println("％");
  Serial.println(analogRead(analogPin));
  delay(1000);

}

#define FILTER_A 2  //阈值
int Filter(){
  int NewValue;
  NewValue = analogRead(analogPin)+8;
  if(((NewValue-Value)>FILTER_A)||(Value-NewValue)>FILTER_A)
  return Value;
  else
  return NewValue; 
}
//对ADC原始值进行限幅滤波
