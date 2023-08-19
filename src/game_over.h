#ifndef CNAKE_GAME_OVER_H
#define CNAKE_GAME_OVER_H

#include "raylib.h"
#include "types.h"

static void handle_game_over(const u32 screen_width, const u32 screen_height, GameState* state);
static void draw_game_over(const u32 screen_width, const u32 screen_height);

static void handle_game_over(const u32 screen_width, const u32 screen_height, GameState* state) {
        if (IsKeyPressed(KEY_R)) {
                *state = RESTART;
        }

        BeginDrawing();
                draw_game_over(screen_width, screen_height);
        EndDrawing();
}

static void draw_game_over(const u32 screen_width, const u32 screen_height) {
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
