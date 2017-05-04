#include "TM4C123.h"                    // Device header
#include "gpio.h"
uint8_t psctl[256] __attribute__((aligned(1024)));
typedef struct
{
	unsigned ps;
	unsigned dst;
	uint32_t ctr;
	uint32_t RESEVER;
}PTR_TYPE;
PTR_TYPE * ctltable;
uint8_t x[8];
#define chn		15U
void GPIOF_Handler(void)
	{
		if(GPIOF->RIS & GPIO_PIN_4)
		{
			GPIO_Write(GPIOF,GPIO_PIN_1);
			ctltable = (PTR_TYPE *)&psctl;
			ctltable[chn].ps				= (uint32_t)GPIOF_BASE+0x40;
			ctltable[chn].dst			= (uint32_t) &x+8;
			ctltable[chn].ctr			= 0x0C000081;
			UDMA->ENASET	|=(1UL<<15UL);
			GPIOF->ICR = GPIO_PIN_4;
		}
	}
int main(void)
{
	SYSCTL->RCGCDMA = 0x01;
	UDMA->CFG				= 0x01;
	UDMA->CTLBASE		= (((uint32_t)&psctl));
	UDMA->PRIOCLR	|= (1UL<<15UL);
	UDMA->USEBURSTCLR|= (1UL<<15UL);
	UDMA->REQMASKCLR	|=(1UL<<15UL);
	UDMA->CHASGN			|= (1UL<<15UL);
	UDMA->CHMAP1			|= (3<<28);
	GPIO_DinInit(GPIOF,GPIO_PIN_4|GPIO_PIN_1,0x02);
	GPIO_IntConfig(GPIOF,GPIO_PIN_4,GPIO_PIN_4,GPIO_PIN_4,0);
	GPIOF->DMACTL 		|= GPIO_PIN_4;	
	while(1)
	{
//		UDMA->SWREQ |= (1UL<<15UL);
		if(GPIO_Read(GPIOF)&GPIO_PIN_4)
		{
			GPIO_Write(GPIOF,0);
		}
	}
}
	