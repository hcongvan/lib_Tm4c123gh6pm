#ifndef __GPIO_H
#define __GPIO_H
#include "TM4C123GH6PM.h"
//First active clock for port in RCGCGPIO
//define to segment of GPIO
#define GPIO_F				0x00000020
#define GPIO_E				0x00000010
#define GPIO_D				0x00000008
#define GPIO_C				0x00000004
#define GPIO_B				0x00000002
#define GPIO_A				0x00000001
//Second	define mode to use for the port
//Example use Digital : GPIODIR to configure direction
//Analog: GPIOAMSEL to configure pin read analog
//Alternate function: GPIOAFSEL and GPIOPCTL configure pin use other activity
//Finally, set pin to use in GPIODEN
//define pin 
#define GPIO_PIN_0				0x00000001
#define GPIO_PIN_1				0x00000002
#define GPIO_PIN_2				0x00000004
#define GPIO_PIN_3				0x00000008
#define GPIO_PIN_4				0x00000010
#define GPIO_PIN_5				0x00000020
#define GPIO_PIN_6				0x00000040
#define GPIO_PIN_7				0x00000080
//define useful GPIOPCTL
//see table GPIO pins and alternate function pages 1351(function 23.4)
//document Tiva™ TM4C123GH6PM Microcontroller Datasheet(Rev. E)
#define GPIO_FUNC_1				1U
#define GPIO_FUNC_2				2U
#define GPIO_FUNC_3				3U
#define GPIO_FUNC_4				4U
#define GPIO_FUNC_5				5U
#define GPIO_FUNC_6				6U
#define GPIO_FUNC_7				7U
#define GPIO_FUNC_8				8U
#define GPIO_FUNC_9				9U
#define GPIO_FUNC_14			14U
//option, using INTERRUPT :
//1: clear IME field in GPIOIM
//2:configure IS field in GPIOIS: 0-The edge on the corresponding pin is detected (edge-sensitive).
//																1-The level on the corresponding pin is detected (level-sensitive).
//and IBE field in GPIOIBE:0-Interrupt generation is controlled by the GPIO Interrupt Event (GPIOIEV) register (see page 666).
//													1-Both edges on the corresponding pin trigger an interrupt.
//configure IEV field in GPIOIEV : 0-A falling edge or a Low level on the corresponding pin triggersan interrupt.
//																	1-A rising edge or a High level on the corresponding pin triggersan interrupt.
//3:clear bit IC field corresponding pin in GPIOICR;
//use NIVC_Interrupt_Enable(IRQ)
//Call void GPIO_x_Handler(void) corresponding code


extern void GPIO_AinInit(GPIOA_Type * gpio,unsigned char pin);
extern void GPIO_DinInit(GPIOA_Type * gpio,unsigned char pin,unsigned char pin_dir);
extern void GPIO_AFInit(GPIOA_Type * gpio, unsigned char pin, unsigned char function);
extern void GPIO_DigDisable(GPIOA_Type * gpio,unsigned char pin);
extern void GPIO_DigEnable(GPIOA_Type * gpio,unsigned char pin);
extern void GPIO_IntEnable(unsigned port);
extern void GPIO_IntConfig(GPIOA_Type * gpio, unsigned char pin, unsigned char sense, unsigned char event, unsigned char edge);
extern int GPIO_Unlock(GPIOA_Type * gpio, unsigned char pin);
extern uint32_t GPIO_Read(GPIOA_Type * gpio);
extern void GPIO_Write(GPIOA_Type * gpio,unsigned long data);
#endif