#ifndef __SGP30_H
#define __SGP30_H
#include "main.h"


#define SGP30_read  0xb1  //SGP30�Ķ���ַ
#define SGP30_write 0xb0  //SGP30��д��ַ

#define ACK         0             //Ӧ���ź�
#define NACK        1             //��Ӧ���ź�

sbit SCL = P1^6;  //SGP30��SCL���Ŷ���
sbit SDA = P1^7;	//SGP30��SDA���Ŷ���



//I2C��ʼ�ź�
void I2CStart(void);

//I2Cֹͣ�ź�
void I2CStop(void);

//I2Cдһ���ֽ����ݣ�����ACK����NACK
u8 I2C_Write_Byte(u8 Write_Byte);

//I2C��һ���ֽ����ݣ���ڲ������ڿ���Ӧ��״̬��ACK����NACK
u8 I2C_Read_Byte(u8 AckValue);

//��ʼ��SGP30
void SGP30_Init(void);

//��SGP30д����
void SGP30_Write(u8 a, u8 b);

//��SGP30������
u32 SGP30_Read(void);


#endif
