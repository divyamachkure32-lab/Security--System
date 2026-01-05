/**
 * Delay Functions Implementation
 */

#include "delay.h"

// Simple delay functions using loops
// Note: These are approximate delays

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) {
        for (uint32_t j = 0; j < 1000; j++) {
            __asm volatile ("nop");
        }
    }
}

void delay_us(uint32_t us) {
    for (uint32_t i = 0; i < us; i++) {
        for (uint32_t j = 0; j < 10; j++) {
            __asm volatile ("nop");
        }
    }
}

// More accurate delay using SysTick timer
void systick_delay_ms(uint32_t ms) {
    // Configure SysTick for 1ms interrupts
    SysTick->LOAD = 72000 - 1;  // 72MHz/1000 = 72000
    SysTick->VAL = 0;
    SysTick->CTRL = 0x5;  // Enable SysTick
    
    for (uint32_t i = 0; i < ms; i++) {
        while (!(SysTick->CTRL & 0x10000));  // Wait for COUNTFLAG
    }
    
    SysTick->CTRL = 0;  // Disable SysTick
}
