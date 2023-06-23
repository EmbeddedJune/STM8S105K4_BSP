#ifndef _INC_BSP_H_
#define _INC_BSP_H_

#include "stm8s105k4.h"

void init_PLL(void);
void init_timer4(void);

ISR_HANDLER(TIM4_ISR, _TIM4_OVR_UIF_VECTOR_);
ISR_HANDLER(UART2_RXD, _UART2_R_RXNE_VECTOR_);

#endif /*_INC_BSP_H_*/