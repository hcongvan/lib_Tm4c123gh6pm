#include "I2C0.h"


void I2C_init(void)
{
	
	SYSCTL->RCGCI2C |= 0x01;
	SYSCTL->RCGCGPIO = (1<<1)|(1<<5);
	GPIOB->AFSEL = 0x0C;
	GPIOB->DEN = 0x0C;
	GPIOB->ODR = 0x08;
	GPIOB->PCTL = 0x00003300; //configuration SCL0 SDA0 pin 
	
	GPIOF->AMSEL =0x00;
	GPIOF->DIR = 0x0E;
	GPIOF->DEN = 0x1E;

	I2C0->MCR = 0x10; //eable master I2C0
	I2C0->MTPR = 24; // set sample TPR
}
uint8_t I2C0_check(void)
{
	while((I2C0->MCS)&1);
	return (I2C0->MCS)&0xE; //return status error
}
uint8_t I2C_writeByte(uint32_t addr,uint32_t mode,uint8_t context,bool cmd)
{
	uint8_t error;
	I2C0->MSA =0;
	I2C0->MSA |= (addr<<1);
	
	I2C0->MDR = context;
	
	I2C0->MCS = mode;
	
	error = I2C0_check();
	if(!cmd){ 
		while((I2C0->MCS)&0x40);
		error = (I2C0->MCS)&0xE;
	}
	if (error) GPIOF->DATA = 0x04;
	return error;
}

uint8_t I2C_readByte(uint32_t addr,uint32_t mode,uint8_t *ptr)
{	
	uint8_t error;
	I2C0->MSA = (addr<<1)+1; 
	
	I2C0->MCS = mode;
	error = I2C0_check();
	if(error) GPIOF->DATA = 0x02;
	*ptr = I2C0->MDR;
	while ((I2C0->MCS)&0x40);
	if (error) GPIOF->DATA = 0x04;
	return error;
}
//not use this code
uint8_t I2C_writeBust(uint32_t sl_addr,uint8_t word_addr,uint8_t* buff,uint8_t length)
{
	uint8_t error,i;
	I2C0->MSA =0;
	I2C0->MSA |= (sl_addr<<1);
	
	I2C0->MDR = word_addr;
	
	I2C0->MCS = 0x03;
	
	error = I2C0_check();
	
	for(i=0;i<length-1;i++)
	{
		I2C0->MDR = buff[i];
		I2C0->MCS = 0x01;
		error |= I2C0_check();
	}
	I2C0->MDR = buff[length-1];
	I2C0->MCS = 0x07;
	error |= I2C0_check();
	if (error) GPIOF->DATA = 0x04;
	return error;
	
}
//not use this code
uint8_t I2C_readBust(uint32_t sl_addr,uint8_t word_addr,uint8_t* buff,uint8_t num)
{
	uint8_t error,i,j;
	I2C0->MSA =0;
	I2C0->MSA |= (sl_addr<<1);
	
	I2C0->MDR = word_addr;
	
	I2C0->MCS = 0x03;
	
	error = I2C0_check();
	if ((I2C0->MCS)&(1<<4))
	{
		I2C0->MCS = 0x40;
		return error;
	}
	I2C0->MSA |= (sl_addr<<1)+1;
	I2C0->MCS = 0x0B;
	error |= I2C0_check();
	buff[0] = I2C0->MDR ;
	for(i=1;i<num-1;i++)
	{
		I2C0->MCS = 0x09;
		error |= I2C0_check();
		buff[i] = I2C0->MDR ;
		
	}
	I2C0->MCS = 0x05;
	error |= I2C0_check();
	buff[num-1] = I2C0->MDR ;
	
	if (error) GPIOF->DATA = 0x04;
	return error;
}
