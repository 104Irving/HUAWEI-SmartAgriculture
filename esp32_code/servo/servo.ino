#include <ESP32Servo.h>

Servo servo;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  
  // 将舵机连接到ESP32的GPIO引脚
  servo.attach(32); // GPIO引脚
}

void loop() {
 if (Serial.available() > 0) {
    int angle = Serial.parseInt();
    
    // 如果 angle 不等于 0，说明成功读取到了有效的角度值
    if (angle != 0) {
      // 将角度限制在0到180度之间
      angle = constrain(angle, 0, 180);
      
      // 控制舵机转动到指定角度
      servo.write(angle);
      
      // 显示当前舵机角度
      Serial.print("舵机角度：");
      Serial.println(angle);
    }
  }
}

