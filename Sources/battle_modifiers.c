// Filename: battle_modifiers.c

#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *      Battle Modifiers        *
 *                              *
 ********************************/

// Battle menu entry
void    battleMenu(void) {

    // Creates spoiler and cheat entries
    new_spoiler("Battle");
        new_entry("100% Capture Rate", catch100);
        new_entry_arg("Wild Pokemon Shiny", shinyPokemon, 0, SHINYPOKEMON, TOGGLE);
        new_entry_arg("Stat Stages +6", maxBattleStats, 0, MAXBATTLESTATS, TOGGLE);
        new_entry_arg("Use Z-Moves w/o Z-Crystal", zMoves, 0, ZMOVES, TOGGLE);
        new_line();
    exit_spoiler();
}


// Sets all in-battle stats to +6 ranks
void    maxBattleStats(u32 state) {
    static u32  original;

    // Checks if cheat is enabled from menu and executes if it is
    if (state) {

        // Stores original value in memory
        original = READU32(o_battlestats1);

        static const u8    buffer[] =
        {
            0x80, 0x20, 0x9F, 0xE5, 0x0E, 0x00, 0x52, 0xE1,
            0x1D, 0x00, 0x00, 0x1A, 0x1F, 0x00, 0x2D, 0xE9,
            0x74, 0x20, 0x9F, 0xE5, 0xD0, 0x00, 0x94, 0xE5,
            0x04, 0x30, 0x80, 0xE2, 0x1C, 0x40, 0x80, 0xE2,
            0x04, 0x10, 0x93, 0xE4, 0x00, 0x00, 0x51, 0xE3,
            0xEA, 0x21, 0xC1, 0x15, 0xEB, 0x21, 0xC1, 0x15,
            0xEC, 0x21, 0x81, 0x15, 0xF0, 0x21, 0xC1, 0x15,
            0x04, 0x00, 0x53, 0xE1, 0xF7, 0xFF, 0xFF, 0x1A,
            0x2C, 0x00, 0x9D, 0xE5, 0x88, 0x0A, 0x90, 0xE5,
            0x01, 0x0A, 0x80, 0xE2, 0x08, 0x08, 0x90, 0xE5,
            0x0C, 0x00, 0x90, 0xE5, 0x08, 0x00, 0x90, 0xE5,
            0x04, 0x30, 0x80, 0xE2, 0x1C, 0x40, 0x80, 0xE2,
            0x04, 0x10, 0x93, 0xE4, 0x00, 0x00, 0x51, 0xE3,
            0xEA, 0x21, 0xC1, 0x15, 0xEB, 0x21, 0xC1, 0x15,
            0xEC, 0x21, 0x81, 0x15, 0xF0, 0x21, 0xC1, 0x15,
            0x04, 0x00, 0x53, 0xE1, 0xF7, 0xFF, 0xFF, 0x1A,
            0x1F, 0x00, 0xBD, 0xE8, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x6E, 0x00, 0x0C, 0x0C, 0x0C, 0x0C
        };
        static const u8    buffer10[] =
        {
            0x70, 0x11, 0xF4, 0xEA, 0xA4, 0x77
        };
        static const u8    buffer11[] =
        {
            0xF8, 0x09, 0xF4, 0xEA, 0x80, 0x96
        };

        memcpy((void *)(o_battlestats2), buffer, 0x90);
        switch(gameVer) {
            case 10:
                memcpy((void *)(o_battlestats2 + 0x84), buffer10, 0x06);
                WRITEU32(o_battlestats1, 0xEA0BEE6C);
                break;
            case 11:
                memcpy((void *)(o_battlestats2 + 0x84), buffer11, 0x06);
                WRITEU32(o_battlestats1, 0xEA0BF5E4);
                break;
        }
    } else {

        // Sets value back to original when cheat is disabled
        WRITEU32(o_battlestats1, original);
    }
}

// 100% Catch rate for Pokemon
void	catch100(void) {
    static const u8 buffer[] =
    {
        0x08, 0x00, 0xD0, 0xE5,
        0x03, 0x40, 0x2D, 0xE9,
        0x10, 0x00, 0x9D, 0xE5,
        0x0C, 0x10, 0x9F, 0xE5,
        0x00, 0x00, 0x51, 0xE1,
        0xF8, 0x00, 0x40, 0x02,
        0x10, 0x00, 0x8D, 0x05,
        0x03, 0x80, 0xBD, 0xE8
    };
    memcpy((void *)(o_catch1001), buffer, 0x20);
    switch(gameVer) {
        case 10:
            WRITEU32(o_catch1001 + 0x20, 0x006D839C);
            WRITEU32(o_catch1002, 0xEB04199D);
            break;
        case 11:
            WRITEU32(o_catch1001 + 0x20, 0x006DA1CC);
            WRITEU32(o_catch1002, 0xEB041A45);
            break;
    }
}


// Make wild Pokemon shiny
void	shinyPokemon(u32 state) {
    WRITEU32(o_shiny, (state) ? 0xEA00001C : 0x0A00001C);
}


// Use Z-Moves without the need of a Z-Crystal
void    zMoves(u32 state) {
    if (state) {
        static const u8    buffer[] =
        {
            0x05, 0x40, 0x2D, 0xE9, 0x06, 0x00, 0xA0, 0xE1,
            0x00, 0x00, 0x00, 0xEA, 0x05, 0x40, 0x2D, 0xE9,
            0x50, 0x20, 0x9D, 0xE5, 0x0C, 0x10, 0x9F, 0xE5,
            0x02, 0x00, 0x51, 0xE1, 0xB4, 0x10, 0xD5, 0x01,
            0x00, 0x10, 0xA0, 0x11, 0x05, 0x80, 0xBD, 0xE8
        };

        memcpy((void *)(o_zmoves1), buffer, 0x28);

        switch(gameVer) {
            case 10:
                WRITEU32(o_zmoves1 + 0x28, 0x0078BA28);
                WRITEU32(o_zmoves2 + 0x00, 0xEB0A06CE);
                WRITEU32(o_zmoves2 + 0x70, 0xEB0A06B5);
                WRITEU32(o_zmoves2 + 0x5932C, 0xE3A00001);
                break;
            case 11:
                WRITEU32(o_zmoves1 + 0x28, 0x0078BF60);
                WRITEU32(o_zmoves2 + 0x00, 0xEB0A0D3E);
                WRITEU32(o_zmoves2 + 0x70, 0xEB0A0D25);
                WRITEU32(o_zmoves2 + 0x59CF4, 0xE3A00001);
                break;
        }

    } else {
        WRITEU32(o_zmoves2 + 0x00, 0xE1D510B4);
        WRITEU32(o_zmoves2 + 0x70, 0xE1D510B4);
        switch(gameVer) {
            case 10:
                WRITEU32(o_zmoves2 + 0x5932C, 0xE3A00000);
                break;
            case 11:
                WRITEU32(o_zmoves2 + 0x59CF4, 0xE3A00000);
                break;
        }
    }
}
