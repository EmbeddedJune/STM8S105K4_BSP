#include "stm8s105k4_bsp.h"
#include "hal_led.h"
#include "hal_stdlib.h"
#include "hal_uart.h"

int main()
{
    /* Initialize BSP */
    init_PLL();
    init_timer4();

    /* Initialize HW peripherals */
    led_init();
    uart_init();
    uart_open(0, 9600);
    uart_printf(0, "Hello, world!\n");
    uart_printf(0, "EmbeddedJune UART Test!\n");
    /* Starts main function */
    while (1) {
        led_toggle(0);
        delay(1000);
    }
}