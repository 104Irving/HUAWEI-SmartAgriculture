#ifndef __SGP30_H
#define __SGP30_H
#include "main.h"


#define SGP30_read  0xb1  //SGP30的读地址
#define SGP30_write 0xb0  //SGP30的写地址

#define ACK         0             //应答信号
#define NACK        1             //非应答信号

sbit SCL = P1^6;  //SGP30的SCL引脚定义
sbit SDA = P1^7;	//SGP30的SDA引脚定义



//I2C起始信号
void I2CStart(void);

//I2C停止信号
void I2CStop(void);

//I2C写一个字节数据，返回ACK或者NACK
u8 I2C_Write_Byte(u8 Write_Byte);

//I2C读一个字节数据，入口参数用于控制应答状态，ACK或者NACK
u8 I2C_Read_Byte(u8 AckValue);

//初始化SGP30
void SGP30_Init(void);

//向SGP30写数据
void SGP30_Write(u8 a, u8 b);

//从SGP30读数据
u32 SGP30_Read(void);


#endif
