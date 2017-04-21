#include "TM4C123GH6PM.h"
#include "utils.h"

#define ADC_SS_0			0x00000001
#define ADC_SS_1			0x00000002
#define ADC_SS_2			0x00000004
#define ADC_SS_3			0x00000008

#define ADC_SSMUX_0(x)		(x<<0)
#define ADC_SSMUX_1(x)		(x<<4)
#define ADC_SSMUX_2(x)		(x<<8)
#define ADC_SSMUX_3(x)		(x<<12)
#define ADC_SSMUX_4(x)		(x<<16)
#define ADC_SSMUX_5(x)		(x<<20)
#define ADC_SSMUX_6(x)		(x<<24)
#define ADC_SSMUX_7(x)		(x<<28)

#define ADC_SSPRI_DEFAULT			0x3210
#define ADC_SSPRI_0123				0x0123

#define ADC_SSCTL_D0					BIT0
#define ADC_SSCTL_END0				BIT1
#define ADC_SSCTL_IE0					BIT2
#define ADC_SSCTL_TS0					BIT3
#define ADC_SSCTL_D1					BIT4
#define ADC_SSCTL_END1				BIT5
#define ADC_SSCTL_IE1					BIT6
#define ADC_SSCTL_TS1					BIT7
#define ADC_SSCTL_D2					BIT8
#define ADC_SSCTL_END2				BIT9
#define ADC_SSCTL_IE2					BIT10
#define ADC_SSCTL_TS2					BIT11
#define ADC_SSCTL_D3					BIT12
#define ADC_SSCTL_END3				BIT13
#define ADC_SSCTL_IE3					BIT14
#define ADC_SSCTL_TS3					BIT15
#define ADC_SSCTL_D4					BIT16
#define ADC_SSCTL_END4				BIT17
#define ADC_SSCTL_IE4					BIT18
#define ADC_SSCTL_TS4					BIT19
#define ADC_SSCTL_D5					BIT20
#define ADC_SSCTL_END5				BIT21
#define ADC_SSCTL_IE5					BIT22
#define ADC_SSCTL_TS5					BIT23
#define ADC_SSCTL_D6					BIT24
#define ADC_SSCTL_END6				BIT25
#define ADC_SSCTL_IE6					BIT26
#define ADC_SSCTL_TS6					BIT27
#define ADC_SSCTL_D7					BIT28
#define ADC_SSCTL_END7				BIT29
#define ADC_SSCTL_IE7					BIT30
#define ADC_SSCTL_TS7					BIT31

extern void ADC_Init(ADC0_Type * adc,unsigned char ss,unsigned int pri_ss,unsigned long event_trigger,unsigned long mux,unsigned long ctl);
extern void ADC_SS0_Read(ADC0_Type * adc,unsigned long * ptrvalue,int num);
extern void ADC_SS1_Read(ADC0_Type * adc,unsigned long * ptrvalue,int num);
extern void ADC_SS2_Read(ADC0_Type * adc,unsigned long * ptrvalue,int num);
extern void ADC_SS3_Read(ADC0_Type * adc,unsigned long * ptrvalue,int num);
