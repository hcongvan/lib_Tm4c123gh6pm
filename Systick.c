/*****************************************************
 * FILE NAME : ../Systick.h													 *
 * author : hcongvan																 *
 * PURPOSE : File obtain function Systick						 *
 * date 	: 2/27/2017																 *
 *****************************************************/
#include "Systick.h"
#include "TM4C123GH6PM.h"
#include "core_cm4.h"

void Systick_Init(uint32_t load)
{
	if(load & ~SYSTICK_IS_VALUE)
	{
		//load value interval
		return;
	}
	SysTick->CTRL &= ~SYSTICK_EN;
	SysTick->CTRL |= SYSTICK_SYSCLK|SYSTICK_INTEN;
	SysTick->LOAD = load;
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn,225);
	SysTick->CTRL |= SYSTICK_EN;
}

uint32_t SysTick_Current(void)
{
	return SysTick->VAL;
}