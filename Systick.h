/*****************************************************
 * FILE NAME : ../Systick.h													 *
 * author : hcongvan																 *
 * PURPOSE : File obtain function Systick						 *
 * date 	: 2/27/2017																 *
 *****************************************************/
#include "TM4C123GH6PM.h"
#include "stdint.h"

#define SYSTICK_IS_COUNT 	0x00010000
#define SYSTICK_SYSCLK		0x00000004
#define SYSTICK_INTEN			0x00000002
#define SYSTICK_EN				0x00000001

#define SYSTICK_IS_VALUE	0x00FFFFFF
/*
 * <summary>
 * description :Intialization resource systick
 * @param : load : period of tick
 * @output: empty
 * </summary>
 */
extern void Systick_Init(uint32_t load);
/*
 * <summary>
 * description :Get value of tick in systick
 * @param : empty
 * @output: uint32_t current tick
 * </summary>
 */
extern uint32_t SysTick_Current(void);