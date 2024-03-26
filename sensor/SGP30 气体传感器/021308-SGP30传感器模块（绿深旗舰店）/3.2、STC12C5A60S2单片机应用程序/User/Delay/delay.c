#include "delay.h"
#include "intrins.h"

//延时约1ms
void delay_ms(u16 ms)               
{
	u16 a,b,c;
	for(a=ms;a>0;a--)
		for(b=10;b>0;b--)
			for(c=85;c>0;c--);
}
//短延时
//void delay_us(int n_us)               
//{
//	int j,k;
//	for(j=0;j<n_us;j++)
//	for(k=0;k<1;k++);
//}

//略微延时，约5us
//void delay_5us()    
//{
//	u8 i;

//	_nop_();
//	_nop_();
//	_nop_();
//	i = 10;
//	while (--i);
//}

