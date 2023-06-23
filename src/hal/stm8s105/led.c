#include "stm8s105k4.h"

#define LED_MAX_CH  1

typedef struct led_pin_t {
    PORT_t* port;
    uint8_t pin_num;
    uint8_t state;
} led_pin_t;

static led_pin_t leds[LED_MAX_CH] = {
    { &sfr_PORTE, 5, 0 }
};

void led_init(void)
{
    //DISABLE_INTERRUPTS();
    for (uint8_t i = 0; i < LED_MAX_CH; i++) {
        leds[i].port->DDR.byte |= (1 << leds[i].pin_num);   // output
        leds[i].port->CR1.byte |= (1 << leds[i].pin_num);   // push-pull
    }
    //ENABLE_INTERRUPTS();
}

void led_on(uint8_t ch)
{
    PORT_t* port = leds[ch].port;
    port->ODR.byte |= (1 << leds[ch].pin_num);
}

void led_off(uint8_t ch)
{
    PORT_t* port = leds[ch].port;
    port->ODR.byte &= ~(1 << leds[ch].pin_num);
}

void led_toggle(uint8_t ch)
{
    PORT_t* port = leds[ch].port;
    port->ODR.byte ^= (1 << leds[ch].pin_num);
}