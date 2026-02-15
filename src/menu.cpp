#include <wups.h>
#include <vpad/input.h>
#include <stdint.h>

/**
 * EXTERNAL VARIABLES
 * These are defined in main.cpp. Using 'extern' tells this file
 * to look for them in the other compiled file.
 */
extern float hitboxSize;
extern float aimStrength;
extern bool isMenuOpen;
extern int selectedOption;

/**
 * Handle Menu Navigation
 * This function is called by the VPAD Hook in main.cpp
 */
void handleMenuNavigation(uint32_t trigger, uint32_t hold) {
    // 1. Navigate between Options (DPAD UP/DOWN)
    if (trigger & VPAD_BUTTON_DOWN) {
        selectedOption = 1; // Aim Assist
    } else if (trigger & VPAD_BUTTON_UP) {
        selectedOption = 0; // Hitbox
    }

    // 2. Slider Logic (DPAD LEFT/RIGHT)
    if (selectedOption == 0) { // Hitbox Selection
        if (hold & VPAD_BUTTON_RIGHT) {
            hitboxSize += 0.01f;
        }
        if ((hold & VPAD_BUTTON_LEFT) && hitboxSize > 0.1f) {
            hitboxSize -= 0.01f;
        }
    } 
    else if (selectedOption == 1) { // Aim Assist Selection
        if ((hold & VPAD_BUTTON_RIGHT) && aimStrength < 1.0f) {
            aimStrength += 0.01f;
        }
        if ((hold & VPAD_BUTTON_LEFT) && aimStrength > 0.0f) {
            aimStrength -= 0.01f;
        }
    }
}
