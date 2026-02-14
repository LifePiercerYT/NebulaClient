#include <wups.h>
#include <vpad/input.h>
#include <coreinit/thread.h>

/**
 * PLUGIN METADATA
 */
WUPS_PLUGIN_NAME("LifePiercer");
WUPS_PLUGIN_DESCRIPTION("LifePiercer");
WUPS_PLUGIN_VERSION("v1.0");
WUPS_PLUGIN_AUTHOR("LifePiercer");

/**
 * GLOBAL VARIABLES
 * Shared with menu.cpp via 'extern'
 */
float hitboxSize = 1.0f;
float aimStrength = 0.0f;
bool isMenuOpen = false;
int selectedOption = 0;

/**
 * PROTOTYPES
 * This tells main.cpp that these functions exist in menu.cpp
 */
void handleMenuNavigation(uint32_t trigger, uint32_t hold);

/**
 * EDUCATIONAL MEMORY POKING
 * This is where the optimization logic happens.
 */
void applyGamePatches() {
    // In a coding class, you would use OSMemory functions here
    // Example: Writing the hitboxSize variable to the game's RAM
}

/**
 * VPAD HOOK
 * Intercepts Wii U GamePad input.
 */
DECL_FUNCTION(int, VPADRead, VPADChan chan, VPADStatus *buffer, uint32_t buffer_size, VPADReadError *error) {
    // Get the real input first
    int result = real_VPADRead(chan, buffer, buffer_size, error);

    if (result > 0) {
        // 1. Check for Menu Toggle: L + R
        if ((buffer->hold & VPAD_BUTTON_L) && (buffer->hold & VPAD_BUTTON_R)) {
            isMenuOpen = !isMenuOpen;
            // Debounce delay to prevent the menu from flickering open/shut
            OSSleepTicks(OSMillisecondsToTicks(200));
        }

        // 2. If the menu is open, redirect D-Pad to our menu logic
        if (isMenuOpen) {
            handleMenuNavigation(buffer->trigger, buffer->hold);
            
            // Run our optimization/utility logic
            applyGamePatches();

            /**
             * CORE LESSON: Input Nullification
             * We set hold/trigger to 0 so the player doesn't 
             * walk off a cliff while you are using the menu.
             */
            buffer->hold = 0;
            buffer->trigger = 0;
            buffer->release = 0;
        }
    }
    return result;
}

// Register the hook with the Aroma environment
WUPS_MUST_REPLACE(VPADRead, "vpad.rpl", "VPADRead");
