/**
 * Delay Functions Header
 */

#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
void systick_delay_ms(uint32_t ms);

#endif // DELAY_H
