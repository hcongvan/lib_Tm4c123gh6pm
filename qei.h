#ifndef __QEI_H
#define __QEI_H
#include "TM4C123GH6PM.h"
#define QEI_FILTCNT(x)	(x<<16)
#define QEI_FILEN				0x00002000
#define QEI_STALLEN			0x00001000
#define QEI_INVI				0x00000800
#define QEI_INVB				0x00000400
#define QEI_INVA				0x00000200
#define QEI_VELDIV1			0x00000000
#define QEI_VELDIV2			0x00000040
#define QEI_VELDIV4			0x00000080
#define QEI_VELDIV8			0x000000C0
#define QEI_VELDIV16		0x00000100
#define QEI_VELDIV32		0x00000140
#define QEI_VELDIV64		0x00000180
#define QEI_VELDIV128		0x000001C0
#define QEI_VELEN				0x00000020
#define QEI_RESMODE			0x00000010
#define QEI_CAPMODE			0x00000008
#define QEI_SIGMODE			0x00000004
#define QEI_SWAP				0x00000002
#define QEI_ENABLE			0x00000001

extern void QEI_Init(QEI0_Type * qei,unsigned long mode, unsigned long load, unsigned long maxpos);
extern void QEI_Disable(QEI0_Type * qei);
extern void QEI_Enable(QEI0_Type * qei);
#endif