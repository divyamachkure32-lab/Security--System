/**
 * Password-Protected Security System
 * LPC1768 ARM Cortex-M3
 * Author: Divya Machkuri
 */

#include "LPC17xx.h"
#include <stdint.h>
#include <string.h>

// LCD Pin Definitions
#define LCD_RS  15  // P0.15
#define LCD_EN  16  // P0.16
#define LCD_D4  17  // P0.17
#define LCD_D5  18  // P0.18
#define LCD_D6  19  // P0.19
#define LCD_D7  20  // P0.20

// Keypad Definitions
#define ROWS_PORT LPC_GPIO1
#define COLS_PORT LPC_GPIO2
#define ROW1 27  // P1.27
#define ROW2 28  // P1.28
#define ROW3 29  // P1.29
#define ROW4 30  // P1.30
#define COL1 2   // P2.2
#define COL2 3   // P2.3
#define COL3 4   // P2.4
#define COL4 5   // P2.5

// Buzzer Pin
#define BUZZER_PIN 0  // P2.0

// System States
typedef enum {
    STATE_IDLE,
    STATE_PASSWORD_ENTER,
    STATE_VERIFYING,
    STATE_ACCESS_GRANTED,
    STATE_ACCESS_DENIED,
    STATE_LOCKOUT
} system_state_t;

// Function Prototypes
void SystemInit(void);
void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_print(const char *str);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
char keypad_scan(void);
void buzzer_beep(uint16_t duration);
void system_lockout(void);
uint8_t verify_password(const char *input);

// Global Variables
static char stored_password[] = "123456";
static char entered_password[7] = {0};
static uint8_t password_index = 0;
static uint8_t failed_attempts = 0;
static system_state_t current_state = STATE_IDLE;

int main(void) {
    SystemInit();
    
    // Initialize peripherals
    lcd_init();
    
    // Configure GPIO for keypad
    ROWS_PORT->FIODIR |= (1 << ROW1) | (1 << ROW2) | (1 << ROW3) | (1 << ROW4);
    COLS_PORT->FIODIR &= ~((1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4));
    
    // Configure buzzer pin
    LPC_GPIO2->FIODIR |= (1 << BUZZER_PIN);
    
    // Initial display
    lcd_clear();
    lcd_print("Security System");
    lcd_set_cursor(1, 0);
    lcd_print("Enter Password:");
    
    while(1) {
        switch(current_state) {
            case STATE_IDLE:
                // Wait for key press
                break;
                
            case STATE_PASSWORD_ENTER:
                // Handle password entry
                break;
                
            case STATE_VERIFYING:
                // Verify password
                break;
                
            case STATE_ACCESS_GRANTED:
                lcd_clear();
                lcd_print("Access Granted!");
                buzzer_beep(100);
                __delay_ms(2000);
                current_state = STATE_IDLE;
                break;
                
            case STATE_ACCESS_DENIED:
                lcd_clear();
                lcd_print("Access Denied!");
                buzzer_beep(500);
                failed_attempts++;
                if(failed_attempts >= 3) {
                    current_state = STATE_LOCKOUT;
                } else {
                    __delay_ms(2000);
                    current_state = STATE_IDLE;
                }
                break;
                
            case STATE_LOCKOUT:
                system_lockout();
                break;
        }
        
        // Keypad scanning
        char key = keypad_scan();
        if(key != 0) {
            if(current_state == STATE_IDLE) {
                current_state = STATE_PASSWORD_ENTER;
                lcd_clear();
                lcd_print("Enter Password:");
                lcd_set_cursor(1, 0);
                password_index = 0;
                memset(entered_password, 0, sizeof(entered_password));
            }
            
            if(key == '#') {
                // Enter key pressed
                entered_password[password_index] = '\0';
                if(verify_password(entered_password)) {
                    current_state = STATE_ACCESS_GRANTED;
                } else {
                    current_state = STATE_ACCESS_DENIED;
                }
            } else if(key == '*') {
                // Clear input
                password_index = 0;
                memset(entered_password, 0, sizeof(entered_password));
                lcd_set_cursor(1, 0);
                lcd_print("            ");
                lcd_set_cursor(1, 0);
            } else if(password_index < 6) {
                // Add digit to password
                entered_password[password_index++] = key;
                lcd_data('*');
            }
        }
    }
}

void SystemInit(void) {
    // System initialization
    SystemCoreClockUpdate();
    
    // Enable clock for GPIO
    LPC_SC->PCONP |= (1 << 15);  // Enable power to GPIO
}

void lcd_init(void) {
    // Configure LCD pins as output
    LPC_GPIO0->FIODIR |= (1 << LCD_RS) | (1 << LCD_EN) | 
                         (1 << LCD_D4) | (1 << LCD_D5) | 
                         (1 << LCD_D6) | (1 << LCD_D7);
    
    __delay_ms(20);
    
    // Initialization sequence for 4-bit mode
    lcd_command(0x33);
    lcd_command(0x32);
    lcd_command(0x28);  // 4-bit, 2 lines, 5x8 font
