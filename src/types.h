#ifndef CNAKE_TYPES_H
#define CNAKE_TYPES_H

#include <stdint.h>

/* Type size */
#define MAX_U8 255

/* Unsigned int types */
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

/* Signed int types */
typedef int32_t  i32;

/* Game Structs */
typedef enum GameState {
        TITLE_SCREEN,
        GAME_OVER,
        PAUSED,
        PLAYING,
        WIN,
        RESTART
} GameState;

#endif
