#include "TM4C123GH6PM.h"
#include "pwm.h"

#define HW(x)			(HALT(x))
#define HALT(x)			(*((volatile unsigned long *) x))

void PWM_GEN_0_Init(PWM0_Type * module,unsigned char pwm,unsigned long ctr,unsigned long capmode)
{
	module->_0_CTL |= ctr;
	if(pwm & 0x01)
		module->_0_GENB |= capmode;
	else
		module->_0_GENA |= capmode;
	module->_0_LOAD	= 0xFFFF;
	module->_0_CMPA	= 0x7FFF;
	module->_0_CMPB	= 0x7FFF;
	module->_0_CTL	|= 0x01;
}
void PWM_GEN_1_Init(PWM0_Type * module,unsigned char pwm,unsigned long ctr,unsigned long capmode)
{
	module->_1_CTL |= ctr;
	if(pwm & 0x01)
		module->_1_GENB |= capmode;
	else
		module->_1_GENA |= capmode;
	module->_1_LOAD	= 0xFFFF;
	module->_1_CMPA	= 0x7FFF;
	module->_1_CMPB	= 0x7FFF;
	module->_1_CTL	|= 0x01;
}
void PWM_GEN_2_Init(PWM0_Type * module,unsigned char pwm,unsigned long ctr,unsigned long capmode)
{
	module->_2_CTL |= ctr;
	if(pwm & 0x01)
		module->_2_GENB |= capmode;
	else
		module->_2_GENA |= capmode;
	module->_2_LOAD	= 0xFFFF;
	module->_2_CMPA	= 0x7FFF;
	module->_2_CMPB	= 0x7FFF;
	module->_2_CTL	|= 0x01;
}
void PWM_GEN_3_Init(PWM0_Type * module,unsigned char pwm,unsigned long ctr,unsigned long capmode)
{
	module->_3_CTL |= ctr;
	if(pwm & 0x01)
		module->_3_GENB |= capmode;
	else
		module->_3_GENA |= capmode;
	module->_3_LOAD	= 0xFFFF;
	module->_3_CMPA	= 0x7FFF;
	module->_3_CMPB	= 0x7FFF;
	module->_3_CTL	|= 0x01;
}

void PWM_Init(PWM0_Type * module,unsigned char pwm, unsigned long ctr,unsigned long capmode)
{
	int i;
	unsigned char gen;
	if(module == PWM1)
			SYSCTL->RCGCPWM |= 0x02;
	else if(module == PWM0)
			SYSCTL->RCGCPWM |= 0x01;
	for(i=0;i<100;i++);
	gen = pwm>>1;
	module->CTL |= (uint32_t)(1UL<<gen);
	switch (gen)
	{
		case PWM_GEN_0:
			PWM_GEN_0_Init(module,pwm,ctr,capmode);
			break;
		case PWM_GEN_1:
			PWM_GEN_1_Init(module,pwm,ctr,capmode);
			break;
		case PWM_GEN_2:
			PWM_GEN_2_Init(module,pwm,ctr,capmode);
			break;
		case PWM_GEN_3:
			PWM_GEN_3_Init(module,pwm,ctr,capmode);
			break;
	}
	module->ENABLE |= (uint32_t)(1UL<<pwm);								
}

void PWM_LoadB(PWM0_Type * module,unsigned char pwm, unsigned long load,unsigned long cmp)
{
	unsigned char gen;
	gen = pwm>>1;
	switch (gen)
	{
		case PWM_GEN_0:
			module->_0_LOAD = load;
			if (pwm&0x01)
				module->_0_CMPA = cmp;
			else
				module->_0_CMPB = cmp;
			break;
		case PWM_GEN_1:
			module->_1_LOAD = load;
			if (pwm&0x01)
				module->_0_CMPA = cmp;
			else
				module->_0_CMPB = cmp;
			break;
		case PWM_GEN_2:
			module->_2_LOAD = load;
			if (pwm&0x01)
				module->_0_CMPA = cmp;
			else
				module->_0_CMPB = cmp;
			break;
		case PWM_GEN_3:
			module->_3_LOAD = load;
			if (pwm&0x01)
				module->_0_CMPA = cmp;
			else
				module->_0_CMPB = cmp;
			break;
	}
}
void PWM_SYSCLOCK(unsigned long clock_div)
{
	int i;
	SYSCTL->RCC 		|= (1UL<<20);
	SYSCTL->RCC			|= clock_div;
	for(i=0;i<100;i++);
}
void PWM_Enable(PWM0_Type * module,unsigned char pwm)
{
	module->ENABLE |= pwm;
}
void PWM_Disable(PWM0_Type * module, unsigned char pwm)
{
	module->ENABLE &= ~pwm;
}
