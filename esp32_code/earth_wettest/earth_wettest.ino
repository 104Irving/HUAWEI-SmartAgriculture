//LingShun Lab
 
 
 
#define Moisture 2 //定义AO 引脚 为 D2
 
#define DO 4        //定义DO 引脚 为 D4
 
 int data1;
 int data2;
 int data3;
 float ave;
float per;
void setup() {
 
  pinMode(Moisture, INPUT);//定义A0为输入模式
 
  pinMode(DO, INPUT);
 
  Serial.begin(9600);
 
}
 
void loop() {
 
data1=analogRead(Moisture);
data2=analogRead(Moisture);
data3=analogRead(Moisture);
 ave=(data1+data2+data3)/3;
per=(1-((ave-1400)/800))*100;
  //串口返回测量数据
 
  //Serial.print("Moisture=");

  Serial.print("原始值：");
 Serial.print(analogRead(Moisture));
Serial.print("|均值：");
  Serial.print((data1+data2+data3)/3);//读取AO的数值

  Serial.print("|湿润程度：");
 Serial.print(per);
Serial.print("%");
if(per<20)
{
  Serial.println("当前土壤非常干旱，需要大量灌溉");
}
else if(per<50)
{
  Serial.println("当前土壤较为干旱，需要少量灌溉");
}
else if(per<70)
{
  Serial.println("当前土壤湿润，不需要量灌溉");
}
else 
{
  Serial.println("当前土壤过于湿润，需要减少水分");
}
 // Serial.print("|DO=");
 // Serial.println(digitalRead(DO));//读取DO的数值
 
  delay(1000);
 
}