#include "TM4C123GH6PM.h"                    // Device header
#include "eeprom.h"

int EEPROM_Init(void)
{
	int i;
	SYSCTL->RCGCEEPROM = 0x01;
	for(i=0;i<6;i++);
	while(((EEPROM->EEDONE) & 0x01));
	if((EEPROM->EESUPP)&0x0C)
	{
		return -1;
	}
	SYSCTL->SREEPROM |= 0x01;
	for(i=0;i<6;i++);
	SYSCTL->SREEPROM &= ~0x01;
	while(((EEPROM->EEDONE) & 0x01));
	if((EEPROM->EESUPP)&0x0C)
	{
		return -1;
	}
	return 0;
}
int EEPROM_write(unsigned long * data,unsigned long address,unsigned int count)
{
	while(((EEPROM->EEDONE) & 0x01));
	EEPROM->EEBLOCK = (address<<6);
	EEPROM->EEOFFSET = ((address>>2)&0x0F);
	while(count>0)
	{
		EEPROM->EERDWR = *data;
		while(((EEPROM->EEDONE) & 0x01));
		data++;
		count--;
		(EEPROM->EEOFFSET)++;
		if((EEPROM->EEOFFSET) == 0)
		{
			(EEPROM->EEBLOCK) ++;
		}
	}
	return 0;
}
int EEPROM_read(unsigned long * data, unsigned long address,unsigned int length)
{
	while(((EEPROM->EEDONE) & 0x01));
	EEPROM->EEBLOCK = (address<<6);
	EEPROM->EEOFFSET = ((address>>2)&0x0F);
	while(length>0)
	{
		*data = EEPROM->EERDWR;
		data++;
		length--;
		(EEPROM->EEOFFSET)++;
		if((EEPROM->EEOFFSET) == 0)
		{
			(EEPROM->EEBLOCK) ++;
		}
	}
	return 0;
}
