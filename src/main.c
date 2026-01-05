/**
 * Password Security System - Main Application
 * LPC1768 ARM Cortex-M3
 * Author: Machkuri Divya
 */

#include "LPC17xx.h"
#include "lcd.h"
#include "keypad.h"
#include "buzzer.h"
#include "system_config.h"
#include "delay.h"
#include <string.h>

// Global variables
char entered_password[PASSWORD_LENGTH + 1];
uint8_t password_index = 0;
uint8_t max_attempts = 3;
uint8_t attempts = 0;

// Function prototypes
void system_init(void);
void display_welcome_message(void);
void clear_password_buffer(void);
void process_password_entry(void);
void grant_access(void);
void deny_access(void);
void system_lockout(void);

int main(void) {
    system_init();
    display_welcome_message();
    
    while (1) {
        process_password_entry();
        
        // Check if max attempts reached
        if (attempts >= max_attempts) {
            system_lockout();
        }
    }
    
    return 0;
}

/**
 * Initialize all system components
 */
void system_init(void) {
    // Initialize peripherals
    lcd_init();
    keypad_init();
    buzzer_init();
    
    // Clear password buffer
    clear_password_buffer();
    
    // Set system to idle state
    LPC_GPIO0->FIOCLR = BUZZER_PIN;
}

/**
 * Display welcome message on LCD
 */
void display_welcome_message(void) {
    lcd_cmd_write(0x01);  // Clear display
    lcd_str_write("Password Security");
    lcd_cmd_write(0xC0);  // Move to second line
    lcd_str_write("System v1.0");
    delay_ms(2000);
    
    lcd_cmd_write(0x01);
    lcd_str_write("Enter Password:");
    lcd_cmd_write(0xC0);  // Move to second line for input
}

/**
 * Clear password buffer
 */
void clear_password_buffer(void) {
    for (uint8_t i = 0; i < PASSWORD_LENGTH + 1; i++) {
        entered_password[i] = '\0';
    }
    password_index = 0;
}

/**
 * Process password entry from keypad
 */
void process_password_entry(void) {
    char key = keypad_get_key();
    
    if (key != 0) {
        // Handle special keys
        if (key == '#') {
            // Confirm password
            entered_password[password_index] = '\0';
            
            if (strcmp(entered_password, PASSWORD) == 0) {
                grant_access();
            } else {
                deny_access();
                attempts++;
            }
            
            clear_password_buffer();
            display_welcome_message();
            
        } else if (key == '*') {
            // Clear/Cancel
            clear_password_buffer();
            lcd_cmd_write(0xC0);
            lcd_str_write("                ");  // Clear line
            lcd_cmd_write(0xC0);
            
        } else if (password_index < PASSWORD_LENGTH) {
            // Store digit
            entered_password[password_index] = key;
            password_index++;
            
            // Display '*' on LCD
            lcd_data_write('*');
            
            // Short beep for key press
            buzzer_beep(50);
        }
    }
}

/**
 * Grant access - correct password
 */
void grant_access(void) {
    lcd_cmd_write(0x01);
    lcd_str_write("Access Granted!");
    lcd_cmd_write(0xC0);
    lcd_str_write("Welcome!");
    
    // Success beep pattern
    buzzer_beep(200);
    delay_ms(100);
    buzzer_beep(200);
    
    // Reset attempts
    attempts = 0;
    
    // Simulate door unlock (can be replaced with relay control)
    LPC_GPIO0->FIOSET = (1 << 12);  // Assuming P0.12 controls lock
    
    delay_ms(3000);  // Keep unlocked for 3 seconds
    
    // Relock
    LPC_GPIO0->FIOCLR = (1 << 12);
}

/**
 * Deny access - wrong password
 */
void deny_access(void) {
    lcd_cmd_write(0x01);
    lcd_str_write("Access Denied!");
    lcd_cmd_write(0xC0);
    lcd_str_write("Wrong Password!");
    
    // Error beep pattern
    buzzer_beep(500);
    
    delay_ms(2000);
    
    // Display attempts remaining
    lcd_cmd_write(0x01);
    lcd_str_write("Attempts Left:");
    lcd_cmd_write(0xC0);
    
    char attempts_str[16];
    sprintf(attempts_str, "%d/%d", max_attempts - attempts, max_attempts);
    lcd_str_write(attempts_str);
    
    delay_ms(2000);
}

/**
 * System lockout after max attempts
 */
void system_lockout(void) {
    lcd_cmd_write(0x01);
    lcd_str_write("SYSTEM LOCKED!");
    lcd_cmd_write(0xC0);
    lcd_str_write("Contact Admin");
    
    // Continuous warning beep
    while (1) {
        buzzer_beep(1000);
        delay_ms(1000);
    }
}
