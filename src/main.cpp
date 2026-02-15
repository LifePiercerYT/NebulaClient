#include <wups.h>
#include <vpad/input.h>
#include <coreinit/thread.h>
#include <coreinit/time.h>

/**
 * GLOBAL VARIABLES
 */
float hitboxSize = 1.0f;
float aimStrength = 0.0f;
bool isMenuOpen = false;
int selectedOption = 0;

/**
 * PROTOTYPES
 */
// If handleMenuNavigation is in another file, the compiler needs to know it's C++
void handleMenuNavigation(uint32_t trigger, uint32_t hold);

void applyGamePatches() {
    // Logic for memory writes goes here
}

/**
 * AROMA/WUPS REQUIREMENT: 
 * These must be inside an extern "C" block so the loader can see them.
 */
extern "C" {
    WUPS_PLUGIN_NAME("NebulaClient");
    WUPS_PLUGIN_DESCRIPTION("NebulaClient");
    WUPS_PLUGIN_VERSION("v1.0");
    WUPS_PLUGIN_AUTHOR("NebulaDev");
    WUPS_PLUGIN_LICENSE("GPL");

    // Define the VPADRead hook
    DECL_FUNCTION(int, VPADRead, VPADChan chan, VPADStatus *buffer, uint32_t buffer_size, VPADReadError *error) {
        int result = real_VPADRead(chan, buffer, buffer_size, error);

        if (result > 0 && buffer) {
            // Toggle Menu: L + R
            if ((buffer->hold & VPAD_BUTTON_L) && (buffer->hold & VPAD_BUTTON_R)) {
                isMenuOpen = !isMenuOpen;
                OSSleepTicks(OSMillisecondsToTicks(200));
            }

            if (isMenuOpen) {
                handleMenuNavigation(buffer->trigger, buffer->hold);
                applyGamePatches();

                // Block game input while menu is open
                buffer->hold = 0;
                buffer->trigger = 0;
                buffer->release = 0;
            }
        }
        return result;
    }

    // Tell Aroma to replace the real VPADRead with ours
    WUPS_MUST_REPLACE(VPADRead, "vpad.rpl", "VPADRead");
}
