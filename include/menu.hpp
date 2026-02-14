#pragma once
#include <stdint.h>

/**
 * SHARED VARIABLES
 * These are defined in main.cpp but used in menu.cpp
 */
extern float hitboxSize;
extern float aimStrength;
extern bool isMenuOpen;
extern int selectedOption;

/**
 * FUNCTION PROTOTYPES
 * This allows main.cpp to call the functions inside menu.cpp
 */

// Handles D-pad movement and slider adjustments
void handleMenuNavigation(uint32_t trigger, uint32_t hold);

// (Optional) Logic for rendering text to the screen
void renderMenuStatus();
