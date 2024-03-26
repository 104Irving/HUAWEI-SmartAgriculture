//LingShun Lab
 
 
 
#define Moisture 2 //定义AO 引脚 为 D2
 
#define DO 4        //定义DO 引脚 为 D4
 
 
 
void setup() {
 
  pinMode(Moisture, INPUT);//定义A0为输入模式
 
  pinMode(DO, INPUT);
 
  Serial.begin(9600);
 
}
 
void loop() {
 
  //串口返回测量数据
 
  Serial.print("Moisture=");
 
  Serial.print(analogRead(Moisture));//读取AO的数值
 
  Serial.print("|DO=");
 
  Serial.println(digitalRead(DO));//读取DO的数值
 
  delay(1000);
 
}