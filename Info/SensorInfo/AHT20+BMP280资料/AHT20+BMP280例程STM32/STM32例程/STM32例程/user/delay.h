#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"	

#define System_Clock 72000000
#define SoftDelay_par		(1.6*((System_Clock/8000000)))
#define SoftDelay_us(x)		{\
	int _dcnt = (int)(x*SoftDelay_par);	\
	while(--_dcnt>0);				\
}
#define SoftDelay_ms(x)	SoftDelay_us(1000UL*x)

#endif
