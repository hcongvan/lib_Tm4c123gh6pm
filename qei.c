#include "qei.h"
#include "TM4C123GH6PM.h"
#include "utils.h"

void QEI_Init(QEI0_Type * qei,unsigned long mode, unsigned long load, unsigned long maxpos)
{
	int i;
	if(qei == QEI0)
		SYSCTL->RCGCQEI |= BIT0;
	else if(qei == QEI1)
		SYSCTL->RCGCQEI |= BIT1;
	for (i=0;i<100;i++);
	qei->CTL |= mode;
	qei->LOAD = load;
	qei->MAXPOS = maxpos;
	qei->CTL |= QEI_ENABLE;
}

void QEI_Disable(QEI0_Type * qei)
{
	qei->CTL &= ~QEI_ENABLE;
}
void QEI_Enable(QEI0_Type * qei)
{
	qei->CTL |= QEI_ENABLE;
}
