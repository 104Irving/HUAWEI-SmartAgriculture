#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "stdio.h"
#include "delay.h"
#include "bsp_i2c.h"
#include "ATH20.h"
#include "BMP280.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);

GPIO_InitTypeDef GPIO_InitStructure;

#pragma import(__use_no_semihosting)
struct __FILE
{
	int handle;

};
FILE __stdout;
_sys_exit(int x)
{
	x = x;
}
int fputc(int ch, FILE *f)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
    USART_SendData(USART1,(uint8_t)ch);
	return ch;
}

void uart_init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
 	USART_DeInit(USART1);  //复位串口1
    //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

    //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口

    USART_Cmd(USART1, ENABLE);                    //使能串口
}

int main(void)
{
    uint8_t ret = 0;
    float P,T,ALT;
    uint32_t CT_data[2];
	int  c1,t1;
    uint8_t LED_Stat = 0;

    RCC_Configuration();					   	//设置系统时钟
    GPIO_Configuration();					    //IO口设
    I2C_Bus_Init();

    uart_init(115200);

    ret = ATH20_Init();
    if(ret == 0)
    {
        printf("AHT20传感器初始化错误\r\n");
        while(1);
    }

    ret = BMP280_Init();
    if(ret != 0x58)
    {
        printf("BMP280传感器初始化错误\r\n");
        while(1);
    }

    while(1)
    {
        /* 读取 ATH20 传感器数据*/
        while(ATH20_Read_Cal_Enable() == 0)
        {
            ATH20_Init();//如果为0再使能一次
            SoftDelay_ms(30);
        }
        ATH20_Read_CTdata(CT_data);  //读取温度和湿度
        c1 = CT_data[0] * 1000 / 1024 / 1024;  //计算得到湿度值（放大了10倍,如果c1=523，表示现在湿度为52.3%）
        t1 = CT_data[1] * 200 *10 / 1024 / 1024 - 500;//计算得到温度值（放大了10倍，如果t1=245，表示现在温度为24.5℃）

        /* 读取 BMP280 传感器数据*/
        BMP280GetData(&P, &T, &ALT);

        printf("***************************\r\n");
        printf("AHT20温湿度传感器测试数据:\r\n");
        printf("温度: %d.%d ℃\r\n",(t1/10),(t1%10));
        printf("湿度: %d.%d %%\r\n",(c1/10),(c1%10));
        printf("\n");
        printf("BMP280传感器测试数据:\r\n");
        printf("气压: %0.4f hPa\r\n",P);
        printf("温度: %0.2f ℃\r\n",T);
        printf("海拔: %0.2f m\r\n",ALT);
        printf("\r\n");

        SoftDelay_ms(1000);

        if(LED_Stat == 0)
        {
            LED_Stat = 1;
            GPIO_ResetBits(GPIOA, GPIO_Pin_2);
        }
        else
        {
            LED_Stat = 0;
            GPIO_SetBits(GPIOA, GPIO_Pin_2);
        }
    }
}

void RCC_Configuration(void)
{
  SystemInit();

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC
  						| RCC_APB2Periph_GPIOD| RCC_APB2Periph_GPIOE , ENABLE);
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;				     //状态LED1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //通用推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
