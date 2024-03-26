/*
1.��Ŀ���ƣ������콢��SGP30ģ��STC89C52���Գ���
2.��ʾģ�飺���ڷ�������,������9600
3.ʹ�������keil4 for 51��keil5 for 51
4.������λ������
5.��Ŀ��ɣ�SGP30ģ��
6.��Ŀ���ܣ����ڷ��ز�����CO2,TVOC����
7.��Ҫԭ������ο�SGP30�����ֲ�
8.�����ַ��https://lssz.tmall.com ���Ա��������������콢�ꡱ
10.��Ȩ�����������콢�����г��������������Ȩ�����뱾���Ʒ���׳��ۣ��벻Ҫ����������׷���䷨�����Σ�
���߶���:(������ʹ�õľ���Ϊ11.0592M)
	VCC--5V
	GND--GND
	SCL--P1.6
	SDA--P1.7
*/
#include "main.h"
#include "stdio.h"
#include "stdio.h"
#include "SGP30.h"
#include "delay.h"


void Uart_Init(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	TI=1;
	ES = 1;
	EA = 1;
}

//void Uart_SendData(u8 dat )
//{
//	SBUF = dat;
//	while(TI == 0);
//	TI = 0;
//}

//void Uart_SendString(char *s)
//{
//	while (*s)              //Check the end of the string
//	{
//		Uart_SendData(*s++);     //Send current char and increment string ptr
//	}
//}


void main(void)
{
	u32 sgp30_dat;
	u16 CO2Data,TVOCData;//����CO2Ũ�ȱ�����TVOCŨ�ȱ�����
	Uart_Init();
	printf("�����콢��SGP30ģ��STC89C52���Գ���\r\n");
	SGP30_Init();   //��ʼ��SGP30
	delay_ms(100);
	SGP30_Write(0x20,0x08);
	sgp30_dat = SGP30_Read();//��ȡSGP30��ֵ
	CO2Data = (sgp30_dat & 0xffff0000) >> 16;
	TVOCData = sgp30_dat & 0x0000ffff;	
	//SGP30ģ�鿪����Ҫһ��ʱ���ʼ�����ڳ�ʼ���׶ζ�ȡ��CO2Ũ��Ϊ400ppm��TVOCΪ0ppd�Һ㶨���䣬����ϵ��ÿ��500ms��ȡһ��
	//SGP30ģ���ֵ�����CO2Ũ��Ϊ400ppm��TVOCΪ0ppd�����͡����ڼ����...����ֱ��SGP30ģ���ʼ����ɡ�
	//��ʼ����ɺ�տ�ʼ�������ݻᲨ���Ƚϴ�������������һ��ʱ�����������ȶ���
	while(CO2Data == 400 && TVOCData == 0)
	{
		SGP30_Write(0x20,0x08);
		sgp30_dat = SGP30_Read();//��ȡSGP30��ֵ
		CO2Data = (sgp30_dat & 0xffff0000) >> 16;//ȡ��CO2Ũ��ֵ
		TVOCData = sgp30_dat & 0x0000ffff;			 //ȡ��TVOCֵ
		printf("���ڼ����...\r\n");
		delay_ms(100);
	}
	while(1)
	{
		SGP30_Write(0x20,0x08);
		(u32)sgp30_dat = (u32)SGP30_Read();//��ȡSGP30��ֵ
		CO2Data = (sgp30_dat & 0xffff0000) >> 16;//ȡ��CO2Ũ��ֵ
		TVOCData = sgp30_dat & 0x0000ffff;       //ȡ��TVOCֵ
		printf("CO2:%dppm\r\nTVOC:%dppd\r\n",CO2Data,TVOCData);
		delay_ms(100);
	}
}

void Uart_Isr() interrupt 4
{
    if (RI)
    {
        RI = 0;  
	}
}

