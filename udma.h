#include "TM4C123GH6PM.h"
extern void uDMA_Init(uint32_t channel);
extern void uDMA_Tranfer(uint32_t channel, uint32_t * src, uint32_t * des , uint32_t count);
extern void uDMA_Tranfer_PingPong(uint32_t channel, uint32_t * prisrc,uint32_t * prides,uint32_t * altsrc,uint32_t * altdes,uint32_t count);
extern void UDMA_Handler(void);