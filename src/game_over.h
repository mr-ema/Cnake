#ifndef CNAKE_GAME_OVER_H
#define CNAKE_GAME_OVER_H

#include "raylib.h"
#include "config.h"
#include "types.h"
#include "game.h"

static void gameOverUpdate(Game* game);
static void gameOverRender(const u32 screen_width, const u32 screen_height);

static void gameOverUpdate(Game* game) {
        if (IsKeyPressed(KEY_R)) {
                game->state = RESTART;
        }
}

static void gameOverRender(const u32 screen_width, const u32 screen_height) {
        const u8 font_size = 50;
        const Color color = RAYWHITE;

        DrawText("GAME OVER",
                screen_width / 2 - MeasureText("GAME OVER", font_size) / 2,
                screen_height / 2 - font_size,
                font_size,
                color
        );

        DrawText("PRESS [R] TO RESTART",
                screen_width / 2 - MeasureText("PRESS [R] TO RESTART", font_size * 0.35) / 2,
                screen_height / 2 + 10,
                font_size * 0.35,
                color
        );
}

#endif
