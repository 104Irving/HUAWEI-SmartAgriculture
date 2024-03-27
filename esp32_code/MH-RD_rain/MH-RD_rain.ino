#define Moisture 2 //定义AO 引脚为 D2
#define DO 4       //定义DO 引脚为 D4

int data[5]; // 用于存储最近5次采样数据
int dataIndex = 0; // 当前数据索引
int numSamples = 5; // 采样次数
float ave; // 平均值
float per;
bool raining = false;

void setup() {
  pinMode(Moisture, INPUT); //定义A0为输入模式
  pinMode(DO, INPUT);
  Serial.begin(9600);
}

void loop() {
  int sum = 0;
  data[dataIndex] = analogRead(Moisture); // 存储当前采样值到数组中
  dataIndex = (dataIndex + 1) % numSamples; // 更新数据索引

  for (int i = 0; i < numSamples; i++) {
    sum += data[i];
  }

  ave = sum / numSamples; // 计算移动平均值

  per = (1 - ((ave - 900) / 1300)) * 100;

  // 判断是否有降水
  if (per > 40) {
    raining = true;
  } else {
    raining = false;
  }

  // 串口返回测量数据
  Serial.print("原始值：");
  Serial.print(analogRead(Moisture));
  Serial.print("|滤波：");
  Serial.print(ave); //读取AO的数值
  Serial.print("|湿润程度：");
  Serial.print(per);
  Serial.print("%");

  if (raining) {
    Serial.println("|当前正在下雨，不需要灌溉");
  } else {
    Serial.print("|降雨不足");
    if (per < 20) {
      Serial.println("|当前土壤非常干旱，需要大量灌溉");
    } else if (per < 50) {
      Serial.println("|当前土壤较为干旱，需要少量灌溉");
    } else if (per < 70) {
      Serial.println("|当前土壤湿润，不需要灌溉");
    } else {
      Serial.println("|当前土壤过于湿润，需要减少水分");
    }
  }

  delay(1000);
}
