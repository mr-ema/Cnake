#ifndef CNAKE_TITLE_SCREEN_H
#define CNAKE_TITLE_SCREEN_H

#include "raylib.h"
#include "types.h"

static void handle_title_screen(const u32 screen_width, const u32 screen_height, GameState* state);
static void draw_title_screen(const u32 screen_width, const u32 screen_height);

static void handle_title_screen(const u32 screen_width, const u32 screen_height, GameState* state) {
        BeginDrawing();
                if (IsKeyPressed(KEY_ENTER)) {
                        *state = PLAYING;
                }

                draw_title_screen(screen_width, screen_height);
        EndDrawing();
}

static void draw_title_screen(const u32 screen_width, const u32 screen_height) {
        const u8 font_size = 40;
        const Color color = BLACK;

        ClearBackground(RAYWHITE);
        DrawText("Press [Enter] To Start The Game!",
                screen_width / 2 - MeasureText("Press [Enter] To Start The Game!", font_size) / 2,
                screen_height / 2 - font_size,
                font_size,
                color
        );
}

#endif
