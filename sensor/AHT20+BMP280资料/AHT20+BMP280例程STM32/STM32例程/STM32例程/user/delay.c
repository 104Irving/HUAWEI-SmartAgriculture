#include "stm32f10x.h"
#include "delay.h"

//void Delay(__IO uint32_t nCount);
//#define System_Clock 72000000
//#define LCD_delay_par		(1.6*((System_Clock/8000000)))
//#define LCD_delay_us(x)		{\
//	int _dcnt = (int)(x*LCD_delay_par);	\
//	while(--_dcnt>0);				\
//}
//#define LCD_delay_ms(x)	LCD_delay_us(1000UL*x)

///* Private function prototypes -----------------------------------------------*/
//void RCC_Configuration(void);
//void GPIO_Configuration(void);

//GPIO_InitTypeDef GPIO_InitStructure;






unsigned char SST25_buffer[4096];
void SPI_Flash_Init(void);
u8 SPI_Flash_ReadByte(void);
u8 SPI_Flash_SendByte(u8 byte);

void wip(void);
void wen(void);
void wdis(void);
void wsr(void);
unsigned char rdsr(void);
void FlashReadID(void);
void sect_clr(unsigned long a1);  
void SST25_R_BLOCK(unsigned long addr, unsigned char *readbuff, unsigned int BlockSize);
void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize);
void SPI_Flash_Init(void);

/****************************************************************************
* ��    �ƣ�void wen(void)
* ��    �ܣ�дʹ��
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void wen(void){
	Select_Flash();
	SPI_Flash_SendByte(0x06);
	NotSelect_Flash();
}

/****************************************************************************
* ��    �ƣ�void wdis(void)
* ��    �ܣ�д��ֹ
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void wdis(void){

	Select_Flash();
	SPI_Flash_SendByte(0x04); 
	NotSelect_Flash();
	wip();
	
}	
/****************************************************************************
* ��    �ƣ�void wsr(void)
* ��    �ܣ�д״̬
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void wsr(void){	
	Select_Flash();
	SPI_Flash_SendByte(0x50);
	NotSelect_Flash(); 
	Select_Flash();
	SPI_Flash_SendByte(0x01);
	SPI_Flash_SendByte(0x00); 
	NotSelect_Flash();
    wip();
}

/****************************************************************************
* ��    �ƣ�void wip(void)
* ��    �ܣ�æ���
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void wip(void){
	unsigned char a=1;
	while((a&0x01)==1) a=rdsr();	

}
/****************************************************************************
* ��    �ƣ�unsigned char rdsr(void)
* ��    �ܣ���״̬�Ĵ���
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
unsigned char rdsr(void){
	unsigned char busy;
	Select_Flash();
	SPI_Flash_SendByte(0x05);
	busy = SPI_Flash_ReadByte();
	NotSelect_Flash();
	return(busy);
	
}

/****************************************************************************
* ��    �ƣ�void SST25_R_BLOCK(unsigned long addr, unsigned char *readbuff, unsigned int BlockSize)
* ��    �ܣ�ҳ��
* ��ڲ�����unsigned long addr--ҳ   unsigned char *readbuff--����   unsigned int BlockSize--����
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/  
void SST25_R_BLOCK(unsigned long addr, unsigned char *readbuff, unsigned int BlockSize){
	unsigned int i=0; 	
	Select_Flash();
	SPI_Flash_SendByte(0x0b);
	SPI_Flash_SendByte((addr&0xffffff)>>16);
	SPI_Flash_SendByte((addr&0xffff)>>8);
	SPI_Flash_SendByte(addr&0xff);
	SPI_Flash_SendByte(0);
	while(i<BlockSize){	
		readbuff[i]=SPI_Flash_ReadByte();
		
		i++;
	}
	NotSelect_Flash();	 	
}
/****************************************************************************
* ��    �ƣ�void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize)
* ��    �ܣ�ҳд
* ��ڲ�����uint32_t addr--ҳ   u8 *readbuff--����   uint16_t BlockSize--����    
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/  
void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize){
	unsigned int i=0,a2;
	sect_clr(addr);   								  //ɾ��ҳ		  
	wsr();
  	wen();	
	Select_Flash();    
	SPI_Flash_SendByte(0xad);
	SPI_Flash_SendByte((addr&0xffffff)>>16);
	SPI_Flash_SendByte((addr&0xffff)>>8);
	SPI_Flash_SendByte(addr&0xff);
  	SPI_Flash_SendByte(readbuff[0]);
	SPI_Flash_SendByte(readbuff[1]);
	NotSelect_Flash();
	i=2;
	while(i<BlockSize){
		a2=120;
		while(a2>0) a2--;
		Select_Flash();
		SPI_Flash_SendByte(0xad);
		SPI_Flash_SendByte(readbuff[i++]);
		SPI_Flash_SendByte(readbuff[i++]);
		NotSelect_Flash();
	}
	
	a2=100;
	while(a2>0) a2--;
	wdis();	
	Select_Flash();	
	wip();
}
/****************************************************************************
* ��    �ƣ�void sect_clr(unsigned long a1)
* ��    �ܣ�ҳ����
* ��ڲ�����unsigned long a1--ҳ   
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void sect_clr(unsigned long a1){
	wsr();
	wen();     
	Select_Flash();	  
	SPI_Flash_SendByte(0x20);
	SPI_Flash_SendByte((a1&0xffffff)>>16);          //addh
	SPI_Flash_SendByte((a1&0xffff)>>8);          //addl 
	SPI_Flash_SendByte(a1&0xff);                 //wtt
	NotSelect_Flash();
	wip();
	
}
/****************************************************************************
* ��    �ƣ�void FlashReadID(void)
* ��    �ܣ��������뼰�ͺŵĺ���
* ��ڲ�����  
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void FlashReadID(void)
{
	Select_Flash();	
  	SPI_Flash_SendByte(0x90);
	SPI_Flash_SendByte(0x00);
	SPI_Flash_SendByte(0x00);
	SPI_Flash_SendByte(0x00);
  	//fac_id= SPI_Flash_ReadByte();		          //BFH: ������SST
	//dev_id= SPI_Flash_ReadByte();	              //41H: �����ͺ�SST25VF016B     
  	NotSelect_Flash();	
}

/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : Initializes the peripherals used by the SPI FLASH driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Flash_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* ���� SPI1 ����: SCK, MISO �� MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //SPI_CS
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  //
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

//	//LCD_RST
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(GPIOE, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);

//	GPIO_SetBits(GPIOE, GPIO_Pin_1);
//	GPIO_SetBits(GPIOB, GPIO_Pin_7);

//  GPIO_SetBits(GPIOC, GPIO_Pin_4);			//��ֹ������·��Ƭѡ
//  GPIO_SetBits(GPIOA, GPIO_Pin_4);			//��ֹENC28J60��Ƭѡ
}

/*******************************************************************************
* Function Name  : SPI_FLASH_ReadByte
* Description    : Reads a byte from the SPI Flash.
*                  This function must be used only if the Start_Read_Sequence
*                  function has been previously called.
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
u8 SPI_Flash_ReadByte(void)
{
  return (SPI_Flash_SendByte(Dummy_Byte));
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SendByte
* Description    : Sends a byte through the SPI interface and return the byte 
*                  received from the SPI bus.
* Input          : byte : byte to send.
* Output         : None
* Return         : The value of the received byte.
*******************************************************************************/
u8 SPI_Flash_SendByte(u8 byte)
{
  /* Loop while DR register in not emplty */
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  //NotSelect_Flash();  while(1);
  /* Send byte through the SPI2 peripheral */
  SPI_I2S_SendData(SPI1, byte);

  /* Wait to receive a byte */
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI1);
}/******************* (C) COPYRIGHT 2011 �ܶ�STM32 *****END OF FILE****/
