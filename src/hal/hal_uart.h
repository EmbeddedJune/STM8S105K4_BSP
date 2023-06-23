#ifndef _HAL_UART_H_
#define _HAR_UART_H_

#include "stdio.h"
#include "stdint.h"
#include "stdarg.h"
#include "stdbool.h"

bool        uart_init(void);
bool        uart_open(uint8_t ch, uint32_t baud);
bool        uart_is_open(uint8_t ch);
bool        uart_close(uint8_t ch);
uint32_t    uart_get_data_length(uint8_t ch);
uint32_t    uart_get_baud(uint8_t ch);
bool        uart_flush(uint8_t ch);
void        uart_put_char(uint8_t ch, uint8_t data);
uint8_t     uart_get_char(uint8_t ch);
uint32_t    uart_write(uint8_t ch, uint8_t* data, uint32_t length);
uint8_t     uart_read(uint8_t ch);
uint32_t    uart_printf(uint8_t ch, const char *fmt, ...);

#endif /*_HAR_UART_H_*/