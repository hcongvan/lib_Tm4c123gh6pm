#include "TM4C123GH6PM.h"

#define PLLDIV2_80M 2
#define PLLDIV2_50M 3
#define PLLDIV2_40M 4
#define PLLDIV2_20M 9

void PLL_Init(unsigned long clock);