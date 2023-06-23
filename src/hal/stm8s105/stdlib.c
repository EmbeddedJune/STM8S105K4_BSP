#include "stm8s105k4.h"

volatile uint32_t timer_tick = 0;

uint32_t millis(void)
{
    uint32_t ret;

    DISABLE_INTERRUPTS();
    ret = timer_tick;
    ENABLE_INTERRUPTS();

    return ret;
}

void delay(uint32_t ms)
{
    uint32_t prev_ms = millis();
    while (millis() - prev_ms < ms);
}