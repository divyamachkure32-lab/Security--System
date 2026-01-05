/**
 * System Configuration File
 */

#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

// System Configuration
#define SYSTEM_VERSION "1.0"
#define PASSWORD_LENGTH 4

// Default Password (Change this in production)
#define PASSWORD "1914"

// Security Settings
#define MAX_ATTEMPTS 3
#define LOCKOUT_TIME 30000  // 30 seconds in milliseconds

// Pin Configuration
#define LOCK_RELAY_PIN (1 << 12)  // P0.12 for door lock relay
#define LED_INDICATOR_PIN (1 << 13)  // P0.13 for status LED

// Timing Configuration
#define DEBOUNCE_DELAY 50
#define DISPLAY_TIMEOUT 10000  // 10 seconds

#endif // SYSTEM_CONFIG_H
