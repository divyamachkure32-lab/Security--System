/**
 * Buzzer Driver Implementation
 */

#include "buzzer.h"
#include "delay.h"

/**
 * Initialize buzzer pin
 */
void buzzer_init(void) {
    LPC_GPIO0->FIODIR |= BUZZER_PIN;
    buzzer_off();
}

/**
 * Turn buzzer on
 */
void buzzer_on(void) {
    LPC_GPIO0->FIOSET = BUZZER_PIN;
}

/**
 * Turn buzzer off
 */
void buzzer_off(void) {
    LPC_GPIO0->FIOCLR = BUZZER_PIN;
}

/**
 * Generate a beep of specified duration
 */
void buzzer_beep(uint16_t duration_ms) {
    buzzer_on();
    delay_ms(duration_ms);
    buzzer_off();
}

/**
 * Success pattern (two short beeps)
 */
void buzzer_pattern_success(void) {
    buzzer_beep(200);
    delay_ms(100);
    buzzer_beep(200);
}

/**
 * Error pattern (one long beep)
 */
void buzzer_pattern_error(void) {
    buzzer_beep(500);
}

/**
 * Warning pattern (three short beeps)
 */
void buzzer_pattern_warning(void) {
    for (uint8_t i = 0; i < 3; i++) {
        buzzer_beep(100);
        delay_ms(100);
    }
}
