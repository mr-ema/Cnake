#ifndef CNAKE_MENU_H
#define CNAKE_MENU_H

#include "raylib.h"
#include "controls.h"
#include "types.h"

typedef enum {
        MAIN_MENU,
        RESUME,
        CONTROLS_MENU,
        CHANGE_LEFT_KEY,
        CHANGE_RIGHT_KEY,
        CHANGE_DOWN_KEY,
        CHANGE_UP_KEY,
        EXIT
} MenuState;

typedef struct {
        const char *label;
        Rectangle rect_bounds;
        MenuState next_state;
} Option;

// TODO: Rewrite this ugly code once I am more familiar with finite-state machines and C.
static void handle_menu(GameState* state);
static void handle_change_key(ControlActions Option, MenuState* state);

static void set_options(Option options[], u8 options_len, u8 font_size);
static void watch_menu(const Option options[], u8 options_len, u8 font_size, MenuState* state);
static bool is_mouse_over(const Option* option);
static bool option_click(const Option* option);

static MenuState menu_state = MAIN_MENU;

static void handle_menu(GameState* state) {
        const u8 menu_options_len = 3;
        const u8 controls_options_len = 4;
        const u8 font_size = 20;

        Option menu_options[] = {
                { .label = " Resume ", .rect_bounds = { 0 }, .next_state = RESUME },
                { .label = "Controls", .rect_bounds = { 0 }, .next_state = CONTROLS_MENU },
                { .label = "  Exit  ", .rect_bounds = { 0 }, .next_state = EXIT },
        };

        Option control_options[] = {
                { .label = "UP   ", .rect_bounds = { 0 }, .next_state = CHANGE_UP_KEY },
                { .label = "DOWN ", .rect_bounds = { 0 }, .next_state = CHANGE_DOWN_KEY },
                { .label = "RIGHT", .rect_bounds = { 0 }, .next_state = CHANGE_RIGHT_KEY },
                { .label = "LEFT ", .rect_bounds = { 0 }, .next_state = CHANGE_LEFT_KEY },
        };

        set_options(control_options, controls_options_len, font_size);
        set_options(menu_options, menu_options_len, font_size);

        switch (menu_state) {
                case MAIN_MENU: 
                        if (IsKeyPressed(get_keybinding(PAUSE_GAME))) {
                                *state = PLAYING;
                        }
                        watch_menu(menu_options, menu_options_len, font_size, &menu_state);
                        break;
                case RESUME:
                        *state = PLAYING;
                        menu_state = MAIN_MENU;
                        break;
                case CONTROLS_MENU:
                        if (IsKeyPressed(get_keybinding(GOBACK))) {
                                menu_state = MAIN_MENU;
                        }
                        watch_menu(control_options, controls_options_len, font_size, &menu_state);
                        break;
                case CHANGE_UP_KEY:
                        handle_change_key(MOVE_UP, &menu_state);
                        break;
                case CHANGE_LEFT_KEY:
                        handle_change_key(MOVE_LEFT, &menu_state);
                        break;
                case CHANGE_RIGHT_KEY:
                        handle_change_key(MOVE_RIGHT, &menu_state);
                        break;
                case CHANGE_DOWN_KEY:
                        handle_change_key(MOVE_DOWN, &menu_state);
                        break;
                case EXIT:
                        *state = EXIT_GAME;
                        break;
        }
}

static void handle_change_key(ControlActions action, MenuState* state) {
        const u8 font_size = 30;
        const Vector2 center = { .x = (float)GetScreenWidth() / 2, .y = (float)GetScreenHeight() / 2 };
        const Color color = RAYWHITE;
        const char* feedback = "[PRESS ENTER TO SET NEW KEY]";

        int key = 0;
        int last_key = get_keybinding(action);
        bool done = false;

        while (!done) {
                if (WindowShouldClose()) {
                        *state = EXIT;
                        done = true;
                } else if (IsKeyPressed(get_keybinding(GOBACK))) {
                        done = true;
                } else if (IsKeyPressed(KEY_ENTER)) {
                        set_keybinding(action, last_key);
                        done = true;
                }

                last_key = key == 0 ? last_key : key;
                key = GetKeyPressed();

                BeginDrawing();
                        ClearBackground(SCREEN_BACKGROUND);
                        DrawText(
                                TextFormat("KEY: %c", last_key),
                                center.x - (float)MeasureText("KEY: c", font_size * 2) / 2,
                                center.y - (font_size * 2),
                                font_size * 2,
                                color
                        );

                        DrawText(
                                feedback,
                                center.x - (float)MeasureText(feedback, font_size) / 2,
                                center.y + (font_size * 3),
                                font_size,
                                color
                        );
                EndDrawing();
        }

        if (*state != EXIT) {
                *state = CONTROLS_MENU;
        }
}

static void draw_option(const Option* option, u8 font_size) {
        const Color color = RAYWHITE;
        const Color hover_color = GREEN;

        bool hovered = is_mouse_over(option);

        DrawText(
                option->label,
                option->rect_bounds.x,
                option->rect_bounds.y,
                font_size,
                hovered ? hover_color : color
        );
}

static void watch_menu(const Option options[], u8 options_len, u8 font_size, MenuState* state) {
        BeginDrawing();
                ClearBackground(SCREEN_BACKGROUND);
                for (u8 i = 0; i < options_len; i++) {
                        if (option_click(&options[i])) {
                                *state = options[i].next_state;
                                break;
                        }

                        draw_option(&options[i], font_size);
                }
        EndDrawing();
}

static void set_options(Option options[], u8 options_len, u8 font_size) {
        u32 start_x = GetScreenWidth() / 2;
        u32 start_y = GetScreenHeight() / 2;

        for (u8 i = 0; i < options_len; i++) {
                float len = MeasureText(options[i].label, font_size);

                options[i].rect_bounds = (Rectangle){
                        .x = start_x - len / 2,
                        .y = (float)start_y - font_size,
                        .width = len,
                        .height = (float)font_size
                };

                start_y = start_y + (font_size * 2);
        }
}

static bool is_mouse_over(const Option* option) {
         return CheckCollisionPointRec(GetMousePosition(), option->rect_bounds);
}

static bool option_click(const Option* option) {
        return (is_mouse_over(option) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

#endif
