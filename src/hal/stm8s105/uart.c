#include "hal_uart.h"
#include "hal_stdlib.h"
#include "qbuffer.h"

#define UART_MAX_CH             1
#define UART_RX_Q_BUFFER_MAX    64      // 64-byte

typedef struct uart_t {
    bool is_open;
    uint32_t baudrate;
    UART2_t* uart_reg;
    uint8_t data[UART_RX_Q_BUFFER_MAX];
    qbuffer_t rx_qbuffer;
} uart_t;

static uart_t uart[UART_MAX_CH];


bool uart_init(void)
{
    uint8_t i;
    for (i = 0; i < UART_MAX_CH; i++) {
        uart[i].is_open = false;
        uart[i].baudrate = 115200;
        qbuffer_create(&uart[i].rx_qbuffer, uart[i].data, UART_RX_Q_BUFFER_MAX);
    }
    return true;
}

bool uart_open(uint8_t ch, uint32_t baud)
{
    bool ret = false;
    uint32_t baud_div;

    switch(ch) {
    case 0:
        uart[ch].uart_reg = &sfr_UART2;
        uart[ch].baudrate = baud;
        baud_div = 16000000/baud;
        
        sfr_PORTD.DDR.DDR5  = 1;    // output (TX)
        sfr_PORTD.CR1.C15   = 1;    // push-pull
        sfr_PORTD.DDR.DDR6  = 0;    // input (RX)
        sfr_PORTD.CR1.C16   = 1;    // pull-up

        // 데이터시트 참고 (BRR1, BRR2 레지스터 초기화)
        sfr_UART2.BRR1.UART_DIV = (baud_div >> 4) & 0xFF;
        sfr_UART2.BRR2.UART_DIV = (baud_div >> 0) & 0x0F;
        sfr_UART2.BRR2.UART_DIV |= (baud_div >> 8) & 0xF0;
        
        // 초기화
        sfr_UART2.CR1.byte = 0x00;
        sfr_UART2.CR2.byte = 0x00;
        sfr_UART2.CR3.byte = 0x00;

        sfr_UART2.CR1.M     = 0;    // 1 start-bit + 8 data bit + n stop bit(CR3 reg)
        sfr_UART2.CR1.PCEN  = 0;    // Parity control disable
        sfr_UART2.CR2.TEN   = 1;    // TX enable
        sfr_UART2.CR2.REN   = 1;    // RX enable
        sfr_UART2.CR2.RIEN  = 1;    // RX Interrupt enable
        sfr_UART2.CR3.STOP  = 0;    // 1 stop bit

        uart[ch].is_open = true;
        ret = true;
        break;
    }
    return ret;
}

bool uart_is_open(uint8_t ch)
{
    return uart[ch].is_open;
}

bool uart_close(uint8_t ch)
{
    uart[ch].uart_reg->CR2.TEN = 0; // TX disable
    uart[ch].uart_reg->CR2.REN = 0; // RX disable
    uart[ch].is_open = false;
    return true;
}

uint32_t uart_get_data_length(uint8_t ch)
{
    return qbuffer_get_length(&uart[ch].rx_qbuffer);
}

uint32_t uart_get_baud(uint8_t ch)
{
    return uart[ch].baudrate;
}

bool uart_flush(uint8_t ch)
{
    qbuffer_flush(&uart[ch].rx_qbuffer);
    return true;
}

void uart_put_char(uint8_t ch, uint8_t data)
{
    uart_write(ch, &data, 1);
}

uint8_t uart_get_char(uint8_t ch)
{
    uint8_t ret = 0;
    while (1) {
        if (uart_get_data_length(ch) > 0) {
            // 한글자만 읽고 break한다.
            ret = uart_read(ch);
            break;
        }
    }
    return ret;
}

uint32_t uart_write(uint8_t ch, uint8_t* data, uint32_t length)
{
    uint32_t ret = 0;
    uint32_t prev_time;
    uint8_t idx = 0;
    UART2_t* reg = uart[ch].uart_reg;

    prev_time = millis();
    while (idx < length) {
        // TX Data register가 비어있다면 1-바이트를 쓴다.
        if (sfr_UART2.SR.TXE) sfr_UART2.DR.byte = data[idx++];
        // UART에 너무 오랜시간이 지체된다면 문제발생으로 본다.
        if (millis() - prev_time > 100) break;
    }
    ret = idx;
    return ret;
}

uint8_t uart_read(uint8_t ch)
{
    uint8_t ret;
    qbuffer_read(&uart[ch].rx_qbuffer, &ret, 1);
    return ret;
}

uint32_t uart_printf(uint8_t ch, const char *fmt, ...)
{
    uint32_t len;
    char buf[128];
    va_list args;
    uint32_t ret;

    va_start(args, fmt);
    len = vsprintf(buf, fmt, args);
    va_end(args);
    ret = uart_write(ch, (uint8_t*)buf, len);

    return ret;
}

ISR_HANDLER(UART2_RXD, _UART2_R_RXNE_VECTOR_)
{
    uint8_t rx_data;
    if (sfr_UART2.SR.RXNE == 1) {
        // RX data register에 데이터가 읽다면 한 글자 읽고 버퍼에 쓴다.
        rx_data = sfr_UART2.DR.byte;
        qbuffer_write(&uart[0].rx_qbuffer, &rx_data, 1);
        sfr_UART2.SR.RXNE = 0;  // 인터럽트 핸들러 처리 완료 기록.
    }
}