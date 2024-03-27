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
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
 	USART_DeInit(USART1);  //��λ����1
    //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

    //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������

    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���
}

int main(void)
{
    uint8_t ret = 0;
    float P,T,ALT;
    uint32_t CT_data[2];
	int  c1,t1;
    uint8_t LED_Stat = 0;

    RCC_Configuration();					   	//����ϵͳʱ��
    GPIO_Configuration();					    //IO����
    I2C_Bus_Init();

    uart_init(115200);

    ret = ATH20_Init();
    if(ret == 0)
    {
        printf("AHT20��������ʼ������\r\n");
        while(1);
    }

    ret = BMP280_Init();
    if(ret != 0x58)
    {
        printf("BMP280��������ʼ������\r\n");
        while(1);
    }

    while(1)
    {
        /* ��ȡ ATH20 ����������*/
        while(ATH20_Read_Cal_Enable() == 0)
        {
            ATH20_Init();//���Ϊ0��ʹ��һ��
            SoftDelay_ms(30);
        }
        ATH20_Read_CTdata(CT_data);  //��ȡ�¶Ⱥ�ʪ��
        c1 = CT_data[0] * 1000 / 1024 / 1024;  //����õ�ʪ��ֵ���Ŵ���10��,���c1=523����ʾ����ʪ��Ϊ52.3%��
        t1 = CT_data[1] * 200 *10 / 1024 / 1024 - 500;//����õ��¶�ֵ���Ŵ���10�������t1=245����ʾ�����¶�Ϊ24.5�棩

        /* ��ȡ BMP280 ����������*/
        BMP280GetData(&P, &T, &ALT);

        printf("***************************\r\n");
        printf("AHT20��ʪ�ȴ�������������:\r\n");
        printf("�¶�: %d.%d ��\r\n",(t1/10),(t1%10));
        printf("ʪ��: %d.%d %%\r\n",(c1/10),(c1%10));
        printf("\n");
        printf("BMP280��������������:\r\n");
        printf("��ѹ: %0.4f hPa\r\n",P);
        printf("�¶�: %0.2f ��\r\n",T);
        printf("����: %0.2f m\r\n",ALT);
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

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;				     //״̬LED1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //ͨ���������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
