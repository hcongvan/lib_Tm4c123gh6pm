#include "PLL.h"

#define PLLCLOCK	400000000
//#define __FPU_PRESENT 1
void PLL_Init(unsigned long clock)
{
	long div2; int Lsb; int result;
	if((clock <= 3125000)||(clock >= 80000000)) return;
	result = PLLCLOCK/clock;
	if(result&0x01)
	{
		Lsb = 0;
		div2 = result/2;
	}
	else
	{
		Lsb = 1;
		div2 = result/2 -1 ;
	}
	SYSCTL->RCC2 |= (1<<31); // USERCC2
	SYSCTL->RCC2 |= (1<<11); // PLL bypass2
	
	SYSCTL->RCC = (SYSCTL->RCC &~0x000007C0) + 0x00000540;; //Xtal 16Mhz
	SYSCTL->RCC2 &= ~(7<<4); // main oscillator
	
	SYSCTL->RCC2 &= ~0x00002000; //clear PWRDN (PLL power  down)
	
	SYSCTL->RCC2 |= 1<<30; //PLL 400Mhz
	SYSCTL->RCC2 = (SYSCTL->RCC2&~ 0x1FC00000) + (div2<<23)+ (Lsb<<22);

	while((SYSCTL->RIS&0x00000040)==0){};
	SYSCTL->RCC2 &= ~0x00000800;
}