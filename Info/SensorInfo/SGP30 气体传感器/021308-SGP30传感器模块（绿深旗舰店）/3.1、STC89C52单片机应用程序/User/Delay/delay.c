#include "delay.h"
#include "intrins.h"

//��ʱԼ1ms
void delay_ms(u16 ms)               
{
	u16 a,b;
	for(a=ms;a>0;a--)
		for(b=114;b>0;b--);
}
