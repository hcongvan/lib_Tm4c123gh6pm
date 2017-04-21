#include "TM4C123.h"                    // Device header
#include <stdbool.h>
#include <stdint.h>

#define ERROR_BIT (1<<4)|(1<<1)|(1<<0)
#define RED_ON()		(GPIOF->DATA)|=(1<<1) 
#define RED_OFF()		(GPIOF->DATA)&=~(1<<1)
#define GREEN_ON()		(GPIOF->DATA)|=(1<<3) 
#define GREEN_OFF()		(GPIOF->DATA)&=~(1<<3)
#define BLUE_ON()		(GPIOF->DATA)|=(1<<2) 
#define BLUE_OFF()		(GPIOF->DATA)&=~(1<<2)

void I2C_init(void);
uint8_t I2C0_check(void);
uint8_t I2C_writeByte(uint32_t addr,uint32_t mode,uint8_t context,bool cmd);
uint8_t I2C_readByte(uint32_t addr,uint32_t mode,uint8_t *ptr);
uint8_t I2C_writeBust(uint32_t sl_addr,uint8_t word_addr,uint8_t* buff,uint8_t length);
uint8_t I2C_readBust(uint32_t sl_addr,uint8_t word_addr,uint8_t* buff,uint8_t num);