#include <stdint.h>
#ifndef __O
#define __O		volatile const
#endif

#ifndef __IO
#define __IO		volatile
#endif

typedef struct
{
  __IO uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[24U];
  __IO uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RSERVED1[24U];
  __IO uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[24U];
  __IO uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[24U];
  __IO uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32_t RESERVED4[56U];
  __IO uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32_t RESERVED5[644U];
  __O  uint32_t STIR;                   /*!< Offset: 0xE00 (R/)  Software Trigger Interrupt Register */
}  NVICType;
typedef struct
{
	__O uint32_t CPUID;
	__IO uint32_t INTCRL;
	__IO uint32_t VTABLE;
	__IO uint32_t APPINT;
	__IO uint32_t SYSCTRL;
	__IO uint32_t CFGCTRL;
	__IO uint32_t SYSPRI[3];
	__IO uint32_t SYSHNDCTRL;
	__IO uint32_t FAULTSTAT;
	__IO uint32_t HFAULTSTAT[2];
	__IO uint32_t MMADDR;
	__IO uint32_t FAULTADDR;
}SCBType;

#define CORE_PERI					(0xE000E000UL)
#define	SYSTICKBASE				(CORE_PERI + 0x010UL)
#define NVICBASE					(CORE_PERI + 0x100UL)
#define SCBBASE						(CORE_PERI + 0xD00) 
#define MPUBASE						(CORE_PERI + 0xD90)
#define FPUBASE						(CORE_PERI + 0xF34)

#define _NVIC								((NVICType *) (NVICBASE))
#define _SCB									((SCBType *)		(SCBBASE))

static inline void NVIC_Enable(int IRQ)
{
	if ((int32_t)(IRQ) >= 0)
  {
    _NVIC->ISER[(((uint32_t)(int32_t)IRQ) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQ) & 0x1FUL));
  }
}
static inline void NVIC_Disable(int IRQ)
{
	 if ((int32_t)(IRQ) >= 0)
  {
    _NVIC->ICER[(((uint32_t)(int32_t)IRQ) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQ) & 0x1FUL));
  }
}
static inline void NVIC_SetPrio(int IRQ,uint8_t pri)
{
	if ((int32_t)(IRQ) >= 0)
  {
    _NVIC->IP[((uint32_t)(int32_t)IRQ)]               = (uint8_t)((pri << (5U)) & (uint32_t)0xFFUL);
  }
  else
  {
    _SCB->SYSPRI[(((uint32_t)(int32_t)IRQ) & 0xFUL)-4UL] = (uint8_t)((pri << (5U)) & (uint32_t)0xFFUL);
  }
}