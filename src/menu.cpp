#include <wups.hpp>
#include <vpad/input.h>
#include <string.h>

// External variables shared with main.cpp
extern float hitboxSize;
extern float aimStrength;
extern bool isMenuOpen;
extern int selectedOption;

/**
 * Handle Menu Navigation
 * Logic for moving the "cursor" and sliding values
 */
void handleMenuNavigation(uint32_t trigger, uint32_t hold) {
    // Navigate between Hitbox (0) and Aim Assist (1)
    if (trigger & VPAD_BUTTON_DOWN) {
        selectedOption = 1;
    } else if (trigger & VPAD_BUTTON_UP) {
        selectedOption = 0;
    }

    // Slider Logic: Right increases, Left decreases
    if (selectedOption == 0) { // Hitbox Selection
        if (hold & VPAD_BUTTON_RIGHT) hitboxSize += 0.05f;
        if (hold & VPAD_BUTTON_LEFT && hitboxSize > 0.1f) hitboxSize -= 0.05f;
    } 
    else if (selectedOption == 1) { // Aim Assist Selection
        if (hold & VPAD_BUTTON_RIGHT && aimStrength < 1.0f) aimStrength += 0.02f;
        if (hold & VPAD_BUTTON_LEFT && aimStrength > 0.0f) aimStrength -= 0.02f;
    }
}

/**
 * Rendering Note:
 * In a .wps plugin, UI is typically rendered using the WUPS Config API
 * which creates a native Wii U sub-menu.
 */
void renderMenuStatus() {
    // This is where you would call OSScreen or WUPS Config functions
    // to display: "Hitbox Size: [|||||---] 1.5x"
}
