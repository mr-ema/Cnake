#ifndef CNAKE_TITLE_SCREEN_H
#define CNAKE_TITLE_SCREEN_H

#include "raylib.h"
#include "snake.h"
#include "types.h"
#include "game.h"
#include "gui.h"

static void titleSceneUpdate(Game* game);
static void titleSceneRender(const u32 screen_width, const u32 screen_height, Game* game);

static void titleSceneUpdate(Game* game) {
        if (IsKeyPressed(KEY_ENTER)) {
                game->state = PLAYING;
        }
}

static void titleSceneRender(const u32 screen_width, const u32 screen_height, Game* game) {
        const u8 font_size = 40;
        const Color color = BLACK;

        const u32 center_x = screen_width / 2;
        const u32 center_y = screen_height / 2;


        ClearBackground(RAYWHITE);
        const char* title_str = "Chose A Mode Or Press [Enter] To Start The Game!";
        DrawText(title_str,
                center_x - MeasureText(title_str, font_size) / 2,
                center_y - font_size,
                font_size,
                color
        );

        const Color btn_color = BLACK;
        const Color hover_color = RED;
        const u16 btn_width = 200;
        const u8 total_buttons = 4;
        const f32 btn_x = (f32)(center_x - ((btn_width + 10) * ((f32)total_buttons / 2)));
        const f32 btn_y = (f32)(center_y + font_size + 40);

        if (CUILabelBtn((Rectangle){ btn_x , btn_y, btn_width, 50}, "Slow", btn_color, hover_color)) {
                game->snake.speed_mode = SLOW;
                game->state = PLAYING;
        } else if (CUILabelBtn((Rectangle){btn_x + btn_width + 10, btn_y, btn_width, 50}, "Normal", btn_color, hover_color)) {
                game->snake.speed_mode = NORMAL;
                game->state = PLAYING;
        } else if (CUILabelBtn((Rectangle){btn_x + (btn_width * 2) + 20, btn_y, btn_width, 50}, "Fast", btn_color, hover_color)) {
                game->snake.speed_mode = FAST;
                game->state = PLAYING;
        } else if (CUILabelBtn((Rectangle){btn_x + (btn_width * 3) + 30, btn_y, btn_width, 50}, "Blazingly fast", btn_color, hover_color)) {
                game->snake.speed_mode = BLAZINGLY_FAST;
                game->state = PLAYING;
        }
}

#endif
