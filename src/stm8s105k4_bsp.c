#include "stm8s105k4_bsp.h"

extern volatile uint32_t timer_tick;

void init_PLL(void)
{
    DISABLE_INTERRUPTS();

    sfr_CLK.CKDIVR.HSIDIV = 0;      // HSI DIV = 1 == 16MHz
    sfr_CLK.ICKR.HSIEN = 1;         // HSI RC Oscillator 활성화(Default)
    while (!sfr_CLK.ICKR.HSIRDY);   // HSI 준비 끝날 때까지 대기

    ENABLE_INTERRUPTS();
}

void init_timer4(void)
{
    DISABLE_INTERRUPTS();

    sfr_TIM4.CR1.CEN = 0;   // Counter disable for initialize

    // TIM4 Control register 설정 - Auto-reloaded update interrupt timer
    sfr_TIM4.CR1.ARPE = 1;  // Auto-reload preload enable
    sfr_TIM4.CR1.OPM = 0;   // Counter is not stopped at update event
    sfr_TIM4.CR1.URS = 0;   // Update Interrupt is triggered as soon as counter overflow
    sfr_TIM4.CR1.UDIS = 0;  // UEV is generated as soon as counter overflow
    
    // 1ms 타이머 만들려면, 16MHz / 64(prescaler) / 250(counter) = 1000us
    sfr_TIM4.PSCR.PSC = 6;  // TIM4 prescaler 2^6 = 64
    sfr_TIM4.ARR.ARR = 249; // TIM4 counter limit = 249 (0~249 = 250개)
    sfr_TIM4.CNTR.CNT = 0;  // Initialize TIM4 counter value
    sfr_TIM4.IER.UIE = 1;   // Update Interrupt enable

    sfr_TIM4.CR1.CEN = 1;   // Counter enable

    ENABLE_INTERRUPTS();
}

// void __interrupt(23) TIM4_ISR(void) { }
ISR_HANDLER(TIM4_ISR, _TIM4_OVR_UIF_VECTOR_)
{
    timer_tick++;
    sfr_TIM4.SR.UIF = 0;            // 초기화를 해줘야 다음 interrupt 실행
}
