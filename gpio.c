#include "TM4C123GH6PM.h"
#include "NVIC_CotexM.h"
#include "gpio.h"
#include "math.h"

void GPIO_RCGC(unsigned  port)
{
	int i;
	switch(port)
	{
		case GPIOA_BASE:
			SYSCTL->RCGCGPIO |= 0x00000001;
			break;
		case GPIOB_BASE:
			SYSCTL->RCGCGPIO |= 0x00000002;
			break;
		case GPIOC_BASE:
			SYSCTL->RCGCGPIO |= 0x00000004;
			break;
		case GPIOD_BASE:
			SYSCTL->RCGCGPIO |= 0x00000008;
			break;
		case GPIOE_BASE:
			SYSCTL->RCGCGPIO |= 0x00000010;
			break;
		case GPIOF_BASE:
			SYSCTL->RCGCGPIO |= 0x00000020;
			break;
	}
	for(i=0;i<100;i++);
}
void GPIO_AinInit(GPIOA_Type * gpio,unsigned char pin)
{
	GPIO_RCGC((unsigned) gpio);
	gpio->DIR &= ~pin;
	gpio->AFSEL |= pin;
	gpio->DEN &= ~pin;
	gpio->AMSEL	|= pin;
}
void GPIO_DinInit(GPIOA_Type * gpio,unsigned char pin,unsigned char pin_dir)
{
	GPIO_RCGC((unsigned) gpio);
	gpio->DIR 	|= pin_dir;
	gpio->AFSEL &= ~pin;
	gpio->AMSEL &= ~pin;
	gpio->PDR		|= pin;
	gpio->DEN  	|= pin;
}
void GPIO_AFInit(GPIOA_Type * gpio, unsigned char pin, unsigned char function)
{
	int i;
	GPIO_RCGC((unsigned) gpio);
	gpio->AFSEL |= pin;
	gpio->AMSEL &= ~pin;
	
	for(i=0x80;i>0;i>>=1) 
	{
		if((i & pin)!= 0)
		{
			int n = log10f(i)/log10f(2);
			gpio->PCTL &= ~(0xF<<((n)*4));
			gpio->PCTL |= (function<<((n)*4));
		}
	}
	gpio->DEN |= pin;
}
void GPIO_DigDisable(GPIOA_Type * gpio,unsigned char pin)
{
	gpio->DEN &= ~pin;
}
void GPIO_DigEnable(GPIOA_Type * gpio,unsigned char pin)
{
	gpio->DEN |= pin;
}
void GPIO_IntConfig(GPIOA_Type * gpio, unsigned char pin, unsigned char sense, unsigned char event, unsigned char edge)
{
	gpio->DEN &= ~pin;
	gpio->IS	|= sense;
	gpio->IEV	|= event;
	gpio->IBE	|= edge;
	gpio->ICR	|= pin;
	gpio->IM	|= pin;
	gpio->DEN	|= pin;
	GPIO_IntEnable((unsigned) gpio);
}

void GPIO_IntEnable(unsigned port)
{
	switch(port)
	{
		case GPIOA_BASE:
			NVIC_Enable(GPIOA_IRQn);
			NVIC_SetPrio(GPIOA_IRQn,7);
			break;
		case GPIOB_BASE:
			NVIC_Enable(GPIOB_IRQn);
			NVIC_SetPrio(GPIOB_IRQn,7);
			break;
		case GPIOC_BASE:
			NVIC_Enable(GPIOC_IRQn);
			NVIC_SetPrio(GPIOC_IRQn,7);
			break;
		case GPIOD_BASE:
			NVIC_Enable(GPIOD_IRQn);
			NVIC_SetPrio(GPIOD_IRQn,7);
			break;
		case GPIOE_BASE:
			NVIC_Enable(GPIOE_IRQn);
			NVIC_SetPrio(GPIOE_IRQn,7);
			break;
		case GPIOF_BASE:
			NVIC_Enable(GPIOF_IRQn);
			NVIC_SetPrio(GPIOF_IRQn,7);
			break;
	}
}
void GPIO_Write(GPIOA_Type * gpio,unsigned long data)
{
	gpio->DATA = data;
}
uint32_t GPIO_Read(GPIOA_Type * gpio)
{
	return(gpio->DATA);
}
int GPIO_Unlock(GPIOA_Type * gpio, unsigned char pin)
{
	if ((gpio->CR) & pin) return 0;
	gpio->LOCK = 0x4C4F434B;
	unsigned commit = (unsigned long)gpio + 0x524;
	*(volatile unsigned long *)commit	|= pin;
}