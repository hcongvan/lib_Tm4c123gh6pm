int EEPROM_Init(void);
int EEPROM_write(unsigned long * data,unsigned long address,unsigned int count);
int EEPROM_read(unsigned long * data, unsigned long address,unsigned int length);