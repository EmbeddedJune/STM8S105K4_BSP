#ifndef _HAL_LED_H_
#define _HAL_LED_H_

#include "stdint.h"

void led_init(void);
void led_on(uint8_t ch);
void led_off(uint8_t ch);
void led_toggle(uint8_t ch);

#endif /*_INC_AP_H_*/