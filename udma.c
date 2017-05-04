#include "udma.h"

uint32_t pstable[256] __attribute__((aligned(1024)));
//#define CHNSW		(UDMA_CHN0_SW0|UDMA_CHN0_SW1|UDMA_CHN1_SW0|UDMA_CHN1_SW1|UDMA_CHN2_SW0|UDMA_CHN2_SW1|UDMA_CHN3_SW0|UDMA_CHN3_SW1|	\\
//								UDMA_CHN3_SW2|UDMA_CHN4_SW0|UDMA_CHN4_SW1|UDMA_CHN2_SW2|UDMA_CHN5_SW0|UDMA_CHN5_SW1|UDMA_CHN6_SW0|UDMA_CHN6_SW1|							\\
//								UDMA_CHN7_SW0|UDMA_CHN7_SW1|UDMA_CHN8_SW0|UDMA_CHN8_SW1|UDMA_CHN9_SW0|UDMA_CHN9_SW1|UDMA_CHN10_SW0|UDMA_CHN11_SW0|							\\
//								UDMA_CHN12_SW0|UDMA_CHN12_SW1|UDMA_CHN13_SW0|UDMA_CHN13_SW1|UDMA_CHN14_SW0|UDMA_CHN15_SW0|UDMA_CHN16_SW0|UDMA_CHN16_SW1|				\\
//								UDMA_CHN17_SW0|UDMA_CHN17_SW1|UDMA_CHN18_SW0|UDMA_CHN19_SW0|UDMA_CHN19_SW1|UDMA_CHN20_SW0|UDMA_CHN20_SW1|UDMA_CHN20_SW2|				\\
//								UDMA_CHN21_SW0|UDMA_CHN21_SW1|UDMA_CHN21_SW2|UDMA_CHN22_SW0|UDMA_CHN22_SW1|UDMA_CHN22_SW2|UDMA_CHN22_SW3|UDMA_CHN23_SW0|				\\
//								UDMA_CHN23_SW1|UDMA_CHN23_SW2|UDMA_CHN23_SW3|UDMA_CHN24_SW0|UDMA_CHN24_SW1|UDMA_CHN25_SW0|UDMA_CHN25_SW1|UDMA_CHN26_SW0|				\\
//								UDMA_CHN26_SW1|UDMA_CHN26_SW2|UDMA_CHN27_SW0|UDMA_CHN27_SW1|UDMA_CHN27_SW2|UDMA_CHN28_SW0|UDMA_CHN28_SW1|UDMA_CHN28_SW2|				\\
//								UDMA_CHN28_SW3|UDMA_CHN29_SW0|UDMA_CHN29_SW1|UDMA_CHN29_SW2|UDMA_CHN29_SW3|UDMA_CHN30_SW0|UDMA_CHN30_SW0|UDMA_CHN30_SW1|				\\
//								UDMA_CHN30_SW2|UDMA_CHN30_SW3|UDMA_CHN30_SW4)																																										\\
								
void UDMA_Init(uint32_t * pctl,uint32_t chn,uint8_t is_alt,uint8_t is_burst,uint8_t prio)
{
	int i,x;
	int chnags,chnmap;
	chnags = chn & 0xFF;
	chnmap = (chn & 0xFF00)>>8U;
	SYSCTL->RCGCDMA = 0x01;
	for(i =0;i<100;i++);
	UDMA->CFG							= 0x01;
	UDMA->CTLBASE					= (uint32_t)(pctl);
	if(prio)
		UDMA->PRIOSET				|= (1UL<<chnags);
	else
		UDMA->PRIOCLR				|= (1UL<<chnags);
	if(is_alt)
		UDMA->ALTSET				|= (1UL<<chnags);
	else
		UDMA->ALTCLR				|= (1UL<<chnags);
	if(is_burst)
		UDMA->USEBURSTSET		|= (1UL<<chnags);
	else
		UDMA->USEBURSTCLR		|= (1UL<<chnags);
	UDMA->REQMASKCLR			|= (1UL<<chnags);
	UDMA->CHASGN					|= (1UL<<chnags);
	x = chnags/8;
	switch(x)
	{
		case 0:
			UDMA->CHMAP0	|= chnmap;
			break;
		case 1:
			UDMA->CHMAP1	|= chnmap;	
			break;
		case 2:
			UDMA->CHMAP2	|= chnmap;
			break;
		case 3:
			UDMA->CHMAP3	|= chnmap;
			break;
	}
}
void UDMA_Transfer(void * src,void * dst,uint32_t ctr,uint32_t chn,uint32_t size)
{
	int chagns;
	chagns = chn & 0xFF;
	UDMA_ctltable * ptr;
	ptr = (UDMA_ctltable *) UDMA->CTLBASE;
	if(ctr & (3UL<<28))
		ptr[chagns].src = (uint32_t) src;
	else
		ptr[chagns].src = (uint32_t) src + size;
	if(ctr & (3UL << 31))
			ptr[chagns].dst = (uint32_t) dst ;
	else
		ptr[chagns].dst = (uint32_t) dst + size;
	ptr[chagns].ctr =  (ctr)|(size<<4U);
	
//	if(chn|CHNSW)
		
	UDMA->ENASET |= (1UL<<chagns);
	
}