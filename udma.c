#include "TM4C123.h"
#include "udma.h"
uint8_t psctlbase[256] __attribute__(( aligned(1024) )); 
uint32_t ch, c;
void uDMA_Init(uint32_t channel)
{
	int i;
	for(i=0;i<256;i++)
	{
		psctlbase[i] = 0;
	}
	SYSCTL->RCGCDMA = 1;
	UDMA->CFG = 1;
	UDMA->CTLBASE = (uint32_t)psctlbase;
	
	UDMA->PRIOCLR |= channel;
	UDMA->ALTCLR  |= channel;
	UDMA->USEBURSTCLR |= channel;
	UDMA->REQMASKCLR |= channel;
	
}

void uDMA_Tranfer(uint32_t channel, uint32_t * src, uint32_t * des , uint32_t count)
{
	psctlbase[channel] = (uint32_t) src+count*4-1;
	psctlbase[channel+1] = (uint32_t) des+count*4-1;
	psctlbase[channel+2] = 0xAA00D002+((count-1)<<4);
	
	UDMA->ENASET |= channel;
	UDMA->SWREQ |= channel;
}
void uDMA_Tranfer_PingPong(uint32_t channel, uint32_t * prisrc,uint32_t * prides,uint32_t * altsrc,uint32_t * altdes,uint32_t count)
{
	psctlbase[channel] = (uint32_t) prisrc+count*4-1;
	psctlbase[channel+1] = (uint32_t) prides+count*4-1;
	psctlbase[channel+2] = 0xAA00D003+((count-1)<<4);
	psctlbase[channel+3] = (uint32_t) altsrc+count*4-1+0x200;
	psctlbase[channel+4] = (uint32_t) altdes+count*4-1+0x200;
	psctlbase[channel+5] = 0xAA00D003+((count-1)<<4);
	
	ch = channel;
	c = count;
	UDMA->ENASET |= channel;
	NVIC_EnableIRQ(UDMA_IRQn);
	NVIC_SetPriority(UDMA_IRQn,(7<<21));
}
void UDMA_Handler(void)
{
	if(!(psctlbase[ch+2]&0x00003FF0))
	{
		psctlbase[ch+2] = 0xAA00D003+((c-1)<<4);
	}
	if(!(psctlbase[ch+5]&0x00003FF0))
	{
		psctlbase[ch+5] = 0xAA00D003+((c-1)<<4);
	}
}