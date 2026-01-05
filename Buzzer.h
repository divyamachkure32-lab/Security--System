/**
 * Buzzer Driver Header
 */

#ifndef BUZZER_H
#define BUZZER_H

#include "LPC17xx.h"
#include <stdint.h>

// Buzzer Pin Definition
#define BUZZER_PIN (1 << 10)  // P0.10

// Function Prototypes
void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);
void buzzer_beep(uint16_t duration_ms);
void buzzer_pattern_success(void);
void buzzer_pattern_error(void);
void buzzer_pattern_warning(void);

#endif // BUZZER_H
