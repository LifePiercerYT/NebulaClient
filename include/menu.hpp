#pragma once
#include <stdint.h>

/**
 * SHARED VARIABLES
 * These are physically located in main.cpp. 
 * 'extern' tells other files to look for them there.
 */
extern float hitboxSize;
extern float aimStrength;
extern bool isMenuOpen;
extern int selectedOption;

/**
 * FUNCTION PROTOTYPES
 * This allows main.cpp to call functions that live in menu.cpp
 */

// Handles D-pad movement and slider adjustments
void handleMenuNavigation(uint32_t trigger, uint32_t hold);

// Logic for rendering text to the screen
void renderMenuStatus();
