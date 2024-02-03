#ifndef CNAKE_GAME_WIN_H
#define CNAKE_GAME_WIN_H

#include "raylib.h"
#include "types.h"
#include "game.h"

static void winSceneUpdate(Game* game);
static void winSceneRender(const u32 screen_width, const u32 screen_height);

static void winSceneUpdate(Game* game) {
        if (IsKeyPressed(KEY_R)) {
                game->state = RESTART;
        }
}

static void winSceneRender(const u32 screen_width, const u32 screen_height) {
        const u8 font_size = 40;
        const Color color = RAYWHITE;

        DrawText("You won the game!",
                 screen_width / 2 - MeasureText("You won the game!", font_size) / 2,
                 screen_height / 2 - font_size,
                 font_size,
                 color
        );
}

#endif
