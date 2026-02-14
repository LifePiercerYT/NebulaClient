#pragma once
#include <stdint.h>

/**
 * ACTUAL OFFSETS: Minecraft Wii U (Patch 43 / 1.13 equivalent)
 * These offsets are relative to the Player Entity pointer.
 */
#define MC_PLAYER_POINTER_ADDR  0x1092F228 // Static pointer to the Local Player
#define OFFSET_HITBOX_WIDTH     0x00000044
#define OFFSET_HITBOX_HEIGHT    0x00000048
#define OFFSET_PLAYER_YAW       0x00000080
#define OFFSET_PLAYER_PITCH      0x00000084

/**
 * BIG-ENDIAN HELPER
 * Wii U uses PowerPC (Big-Endian). This writes data directly to RAM.
 */
static inline void poke_float(uint32_t address, float value) {
    if (address < 0x10000000 || address > 0x40000000) return; // Safety bounds
    *(volatile float*)(address) = value;
}

/**
 * RESOLVE PLAYER BASE
 * Since the player moves in memory, we must follow the pointer.
 */
uint32_t getPlayerBase() {
    uint32_t* ptr = (uint32_t*)MC_PLAYER_POINTER_ADDR;
    if (ptr == nullptr || *ptr == 0) return 0;
    return *ptr; // This is the dynamic address of the player
}

/**
 * UPDATED HITBOX LOGIC
 */
void applyHitboxLogic(float sliderValue) {
    uint32_t playerBase = getPlayerBase();
    if (playerBase == 0) return;

    float baseWidth = 0.6f;
    float newWidth = baseWidth * sliderValue;
    
    // Write actual hitbox dimensions
    poke_float(playerBase + OFFSET_HITBOX_WIDTH, newWidth);
}

/**
 * SMOOTH AIM ASSIST (Conceptual)
 */
void applyAimAssist(float strength) {
    uint32_t playerBase = getPlayerBase();
    if (playerBase == 0 || strength <= 0.0f) return;

    // To add aim assist, you would calculate the enemy's coordinates,
    // then use poke_float to nudge OFFSET_PLAYER_YAW.
}
