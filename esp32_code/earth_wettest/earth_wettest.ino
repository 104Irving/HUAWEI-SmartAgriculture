#include <Arduino.h>

#define MoisturePin 2 // 使用D2引脚用于湿度传感器
#define DO 4           // 定义DO 引脚为 D4
#define NumReadings 10 // 用于滤波的读数数量

int moistureReadings[NumReadings]; // 存储滤波读数
int readIndex = 0;                  // 当前读数的索引
float total = 0;                    // 读数总和
float average = 0;                  // 读数平均值
float moisturePercent = 0;          // 湿度百分比
unsigned long lastPrintTime = 0;    // 上次打印信息的时间

void setup() {
  pinMode(MoisturePin, INPUT);
  Serial.begin(9600);
  // 初始化所有读数为0:
  for (int thisReading = 0; thisReading < NumReadings; thisReading++) {
    moistureReadings[thisReading] = 0;
  }
}

void loop() {
  // 从滤波总和中减去最后一个读数:
  total = total - moistureReadings[readIndex];
  // 读取新的湿度值:
  moistureReadings[readIndex] = analogRead(MoisturePin);
  // 将这个读数添加到total中:
  total = total + moistureReadings[readIndex];
  // 推进到下一个读数位置:
  readIndex = (readIndex + 1) % NumReadings;

  // 计算平均值:
  average = total / NumReadings;
  // 将平均值映射到湿度百分比:
  moisturePercent = (1 - ((average - 1400) / 900)) * 100;

  // 每隔一段时间打印信息:
  if (millis() - lastPrintTime >= 1000) {
    lastPrintTime = millis();
    
    // 打印时间戳和传感器读数:
    Serial.print("时间: ");
    Serial.print(millis() / 1000);
    Serial.print("s | 原始值: ");
    Serial.print(average);
    Serial.print(" | 湿润程度: ");
    Serial.print(moisturePercent);
    Serial.println("%");

    // 根据湿度百分比提供建议:
    if (moisturePercent < 20) {
      Serial.println("警告: 当前土壤非常干旱，需要大量灌溉。");
    } else if (moisturePercent < 50) {
      Serial.println("注意: 当前土壤较为干旱，需要适量灌溉。");
    } else if (moisturePercent < 70) {
      Serial.println("当前土壤湿润，维持当前水分状态即可。");
    } else {
      Serial.println("提醒: 当前土壤过于湿润，应考虑减少灌溉。");
    }
  }
}
