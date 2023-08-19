#ifndef CNAKE_GAME_WIN_H
#define CNAKE_GAME_WIN_H

#include "raylib.h"
#include "types.h"

static void handle_win_state(const u32 screen_width, const u32 screen_height, GameState* state);
static void draw_win_text(const u32 screen_width, const u32 screen_height);

static void handle_win_state(const u32 screen_width, const u32 screen_height, GameState* state) {
        if (IsKeyPressed(KEY_R)) {
                *state = RESTART;
        }

        BeginDrawing();
                draw_win_text(screen_width, screen_height);
        EndDrawing();
}

static void draw_win_text(const u32 screen_width, const u32 screen_height) {
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
