/*
1.项目名称：绿深旗舰店SGP30模块STM32F103C8T6测试程序
2.显示模块：串口返回数据,波特率9600
3.使用软件：keil5 for ARM
4.配套上位机：无
5.项目组成：SGP30模块
6.项目功能：串口返回测量的CO2,TVOC数据
7.主要原理：具体参考SGP30数据手册
8.购买地址：https://lssz.tmall.com 或淘宝上搜索“绿深旗舰店”
10.版权声明：绿深旗舰店所有程序都申请软件著作权。均与本店产品配套出售，请不要传播，以免追究其法律责任！
接线定义
	VCC--5V
	GND--GND
	SCL--PB0
	SDA--PB1
*/

#include "sys.h"
#include "delay.h"
#include "SGP30.h"
#include "usart.h"

u32 CO2Data,TVOCData;//定义CO2浓度变量与TVOC浓度变量

int main(void)
{
	u32 sgp30_dat;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();
	uart_init(9600);
	SGP30_Init();   //初始化SGP30
	delay_ms(100);
	SGP30_Write(0x20,0x08);
	sgp30_dat = SGP30_Read();//读取SGP30的值
	CO2Data = (sgp30_dat & 0xffff0000) >> 16;
	TVOCData = sgp30_dat & 0x0000ffff;	
	//SGP30模块开机需要一定时间初始化，在初始化阶段读取的CO2浓度为400ppm，TVOC为0ppd且恒定不变，因此上电后每隔一段时间读取一次
	//SGP30模块的值，如果CO2浓度为400ppm，TVOC为0ppd，发送“正在检测中...”，直到SGP30模块初始化完成。
	//初始化完成后刚开始读出数据会波动比较大，属于正常现象，一段时间后会逐渐趋于稳定。
	//气体类传感器比较容易受环境影响，测量数据出现波动是正常的，可自行添加滤波函数。
	while(CO2Data == 400 && TVOCData == 0)
	{
		SGP30_Write(0x20,0x08);
		sgp30_dat = SGP30_Read();//读取SGP30的值
		CO2Data = (sgp30_dat & 0xffff0000) >> 16;//取出CO2浓度值
		TVOCData = sgp30_dat & 0x0000ffff;			 //取出TVOC值
		printf("正在检测中...\r\n");
		delay_ms(500);
	}
	while(1)
	{
		SGP30_Write(0x20,0x08);
		sgp30_dat = SGP30_Read();//读取SGP30的值
		CO2Data = (sgp30_dat & 0xffff0000) >> 16;//取出CO2浓度值
		TVOCData = sgp30_dat & 0x0000ffff;       //取出TVOC值
		printf("CO2:%dppm\r\nTVOC:%dppd\r\n",CO2Data,TVOCData);
		delay_ms(500);
	}
}


