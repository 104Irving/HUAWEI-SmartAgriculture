#include "SGP30.h"

void SGP30_IO_Init()
{
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
}



//模拟IIC用的短延时 us

void I2CDelay (u8 t)
{
  while(t--);
}

//I2C起始信号
void SGP::I2CStart(void)
{
  pinMode(SDA, OUTPUT);
  SDA_1;                            //发送起始条件的数据信号 
  SCL_1;
  I2CDelay(50);                    //起始条件建立时间大于4.7us,延时 
  SDA_0;                            //发送起始信号
  I2CDelay(50);                    //起始条件锁定时间大于4μs 
  SCL_0;                            //钳住I2C总线，准备发送或接收数据 
  I2CDelay(50);
}

//I2C停止信号

void SGP::I2CStop(void)
{
  pinMode(SDA, OUTPUT);
  SDA_0;                        //发送结束条件的数据信号 
  SCL_0;
  I2CDelay(50);
  SCL_1;                        //发送结束条件的时钟信号 
  I2CDelay(50);                //结束条件建立时间大于4μs 
  SDA_1;                        //发送I2C总线结束信号 
  I2CDelay(50);
}

//I2C写一个字节数据，返回ACK或者NACK
u8 SGP::I2C_Write_Byte(u8 Write_Byte)  //Sendbyte
{
  u8 i;
  pinMode(SDA, OUTPUT);
  SCL_0;
  I2CDelay(10);
  for(i=0; i<8; i++)            //要传送的数据长度为8位 
  {
    if(Write_Byte&0x80)   //判断发送位 
    {
      SDA_1;
    }
    else
    {
      SDA_0;
    }
    I2CDelay(5);
    SCL_1;                //输出SDA稳定后，拉高SCL给出上升沿，从机检测到后进行数据采样
    I2CDelay(5);         //保证时钟高电平周期大于4μs 
    SCL_0;
    I2CDelay(5);
    Write_Byte <<= 1;
  }
  I2CDelay(1);
  SDA_1;                      //8位发送完后释放数据线，准备接收应答位-ZLG
  I2CDelay(40);
  SCL_1;                      //MCU告知SHT2X数据发送完毕，等待从机的应答信号
  I2CDelay(40);
  pinMode(SDA, INPUT);
  /*以下是判断I2C总线接收应到应答信号是ACK还是NACK*/
  if(digitalRead(SDA)==1)                                   //SDA为高，收到NACK
  {
    I2CDelay(40);
    SCL_0;
    return NACK;
  }
  else                                         //SDA为低，收到ACK
  {
    I2CDelay(40);
    SCL_0;
    return ACK;

  }
}

//I2C读一个字节数据，入口参数用于控制应答状态，ACK或者NACK
u8 SGP::I2C_Read_Byte(u8 AckValue)//receivebyte
{
  u8 i,RDByte=0;
  pinMode(SDA, OUTPUT);
  SCL_0;                                   //置时钟线为低，准备接收数据位 
  I2CDelay(40);
  SDA_1;                                 //释放总线,置数据线为输入方式
  pinMode(SDA, INPUT); 
  for (i=0; i<8; i++)
  {
    SCL_1;                          //SCL高电平期间，采集SDA信号，并作为有效数据 //置时钟线为高使数据线上数据有效 
    I2CDelay(20);
    RDByte <<= 1;                  //移位
    if(digitalRead(SDA)==1)                           //采样获取数据
    {
      RDByte |= 0x01;
    }
    else
    {
      RDByte &= 0xfe;
    }
    I2CDelay(10);
    SCL_0;                             //下降沿，从机给出下一位值
    I2CDelay(60);
  }
  pinMode(SDA, OUTPUT);
  /*以下是I2C总线发送应答信号ACK或者NACK*/
  digitalWrite(SDA, AckValue);                      //应答状态
  I2CDelay(30);
  SCL_1;
  I2CDelay(50);                  //时钟低电平周期大于4μs 
  SCL_0;                                  //清时钟线，钳住I2C总线以便继续接收 
  I2CDelay(150);
  return RDByte;
}


//初始化IIC接口
void SGP::SGP30_Init(void)
{
  SGP30_IO_Init();
  SGP30_Write(0x20,0x03);
//  SGP30_ad_write(0x20,0x61);
//  SGP30_ad_write(0x01,0x00);
}

void SGP::SGP30_Write(u8 a, u8 b)
{
  I2CStart();
  I2C_Write_Byte(SGP30_write); //发送器件地址+写指令
  I2C_Write_Byte(a);    //发送控制字节
  I2C_Write_Byte(b);
  I2CStop();
  delay(100);
}

unsigned long SGP::SGP30_Read(void)
{
  unsigned long dat;
  int crc;
  I2CStart();
  I2C_Write_Byte(SGP30_read); //发送器件地址+读指令
  dat = I2C_Read_Byte(ACK);
  dat <<= 8;
  dat += I2C_Read_Byte(ACK);
  crc = I2C_Read_Byte(ACK); //check数据，舍去
  crc = crc;             //避免编译产生警告，这句可有可无
  dat <<= 8;
  dat += I2C_Read_Byte(ACK);
  dat <<= 8;
  dat += I2C_Read_Byte(NACK);
  I2CStop();
  return(dat);
}
