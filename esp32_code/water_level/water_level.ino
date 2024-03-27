
#define A0 35  
int val = 0; //定义一个变量 val ，初始化值为0
float water_height;
void setup() {
  Serial.begin(115200); // 设置波特率为115200
}

void loop() {
  val = analogRead(A0); // 获取A0模拟口的数据，并赋值给 val 变量
  Serial.print("val = "); // 串口输出 val 当前的数据
  Serial.print(val);
   
  if(val < 200) { // 如果 val 小于200
    Serial.println(" | dry"); // 说明很干，没有水
  } else if(val < 450) { // 如果 小于 450
Serial.println(" | water level: ~ 0-1 cm"); 
// 水位大约在0-1cm ，以下语句如此类推
  } else if(val < 500) {
    Serial.println(" | water level: ~ 1-2 cm");
  } else if(val < 540) {
    Serial.println(" | water level: ~ 2-3 cm");
  } else if(val < 600) {
    Serial.println(" | water level: ~ 3-4 cm");
  } else {
    Serial.println(" | water level: over 4 cm");
  }

  
  delay(1000); // 等待1秒
}