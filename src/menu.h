#ifndef CNAKE_MENU_H
#define CNAKE_MENU_H

#include "raylib.h"
#include "controls.h"
#include "types.h"
#include "game.h"
#include <stdio.h>

typedef enum {
        MAIN_MENU = 0,
        CONTROLS_MENU,
        RESUME,
        BACK_TO_TITLE_SCREEN,
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
static void menuUpdate(GameState* state);
static void menuRender(void);

static void _menuChangeKeyUpdate(ControlActions Option, MenuState* state);
static void _menuChangeKeyDraw(ControlActions action);

static void _menuSetOptions(Option options[], u8 options_len, u8 font_size);
static void _menuWatch(const Option options[], u8 options_len, u8 font_size, MenuState* state);
static void _menuDrawOption(const Option *option, u8 font_size);
static bool _menuIsMouseOver(const Option* option);
static bool _menuOptionClick(const Option* option);

static MenuState menu_state = MAIN_MENU;

static void menuUpdate(GameState* state) {
        switch (menu_state) {
                case MAIN_MENU:
                        if (IsKeyPressed(controlGet(PAUSE_GAME))) {
                                *state = PLAYING;
                        }
                        break;
                case RESUME:
                        *state = PLAYING;
                        menu_state = MAIN_MENU;
                        break;
                case BACK_TO_TITLE_SCREEN:
                        *state = TITLE_SCREEN;
                        menu_state = MAIN_MENU;
                        break;
                case CONTROLS_MENU:
                        if (IsKeyPressed(controlGet(GOBACK))) {
                                menu_state = MAIN_MENU;
                        }
                        break;
                case CHANGE_UP_KEY:
                        _menuChangeKeyUpdate(MOVE_UP, &menu_state);
                        break;
                case CHANGE_LEFT_KEY:
                        _menuChangeKeyUpdate(MOVE_LEFT, &menu_state);
                        break;
                case CHANGE_RIGHT_KEY:
                        _menuChangeKeyUpdate(MOVE_RIGHT, &menu_state);
                        break;
                case CHANGE_DOWN_KEY:
                        _menuChangeKeyUpdate(MOVE_DOWN, &menu_state);
                        break;
                case EXIT:
                        *state = EXIT_GAME;
                        break;
        }
}

static void menuRender(void) {
        const u8 menu_options_len = 4;
        const u8 controls_options_len = 4;
        const u8 font_size = 20;

        Option menu_options[] = {
                { .label = "       Resume       ", .rect_bounds = { 0 }, .next_state = RESUME },
                { .label = "      Controls      ", .rect_bounds = { 0 }, .next_state = CONTROLS_MENU },
                { .label = "Back To Title Screen", .rect_bounds = { 0 }, .next_state = BACK_TO_TITLE_SCREEN },
                { .label = "        Exit        ", .rect_bounds = { 0 }, .next_state = EXIT },
        };

        Option control_options[] = {
                { .label = "UP   ", .rect_bounds = { 0 }, .next_state = CHANGE_UP_KEY },
                { .label = "DOWN ", .rect_bounds = { 0 }, .next_state = CHANGE_DOWN_KEY },
                { .label = "RIGHT", .rect_bounds = { 0 }, .next_state = CHANGE_RIGHT_KEY },
                { .label = "LEFT ", .rect_bounds = { 0 }, .next_state = CHANGE_LEFT_KEY },
        };

        _menuSetOptions(control_options, controls_options_len, font_size);
        _menuSetOptions(menu_options, menu_options_len, font_size);

        switch (menu_state) {
                case MAIN_MENU:
                        _menuWatch(menu_options, menu_options_len, font_size, &menu_state);
                        break;
                case CONTROLS_MENU:
                        _menuWatch(control_options, controls_options_len, font_size, &menu_state);
                        break;
                case CHANGE_UP_KEY:
                        _menuChangeKeyDraw(MOVE_UP);
                        break;
                case CHANGE_LEFT_KEY:
                        _menuChangeKeyDraw(MOVE_LEFT);
                        break;
                case CHANGE_RIGHT_KEY:
                        _menuChangeKeyDraw(MOVE_RIGHT);
                        break;
                case CHANGE_DOWN_KEY:
                        _menuChangeKeyDraw(MOVE_DOWN);
                        break;
                default:
                        break;
        }
}

static void _menuChangeKeyDraw(ControlActions action) {
        const u8 font_size = 30;
        const Vector2 center = { .x = (f32)GetScreenWidth() / 2, .y = (f32)GetScreenHeight() / 2 };
        const Color color = RAYWHITE;
        const char* feedback = "[PRESS ENTER TO SET NEW KEY]";

        int key = controlGet(action);

        ClearBackground(SCREEN_BACKGROUND);
        DrawText(
                TextFormat("KEY: %c", key),
                center.x - (f32)MeasureText("KEY: c", font_size * 2) / 2,
                center.y - (font_size * 2),
                font_size * 2,
                color
        );

        DrawText(
                feedback,
                center.x - (f32)MeasureText(feedback, font_size) / 2,
                center.y + (font_size * 3),
                font_size,
                color
        );
}

static void _menuChangeKeyUpdate(ControlActions action, MenuState* state) {
        // TODO: Make a more decent solution on future rewrite
        static int last_key = 0;
        if (last_key == 0) {
                last_key = controlGet(action);
        }

        int temp_key = GetKeyPressed();

        if (IsKeyPressed(controlGet(GOBACK))) {
                *state = CONTROLS_MENU;
                controlSet(action, last_key);
                last_key = 0;
        } else if (IsKeyPressed(KEY_ENTER)) {
                *state = CONTROLS_MENU;
                last_key = 0;
        } else if (temp_key != KEY_NULL) {
                controlSet(action, temp_key);
        }
}

static void _menuDrawOption(const Option* option, u8 font_size) {
        const Color color = RAYWHITE;
        const Color hover_color = GREEN;

        bool hovered = _menuIsMouseOver(option);

        DrawText(
                option->label,
                option->rect_bounds.x,
                option->rect_bounds.y,
                font_size,
                hovered ? hover_color : color
        );
}

static void _menuWatch(const Option options[], u8 options_len, u8 font_size, MenuState* state) {
        ClearBackground(SCREEN_BACKGROUND);
        for (u8 i = 0; i < options_len; i++) {
                if (_menuOptionClick(&options[i])) {
                        *state = options[i].next_state;
                        break;
                }

                _menuDrawOption(&options[i], font_size);
        }
}

static void _menuSetOptions(Option options[], u8 options_len, u8 font_size) {
        u32 start_x = GetScreenWidth() / 2;
        u32 start_y = GetScreenHeight() / 2;

        for (u8 i = 0; i < options_len; i++) {
                f32 len = MeasureText(options[i].label, font_size);

                options[i].rect_bounds = (Rectangle){
                        .x = start_x - len / 2,
                        .y = (f32)start_y - font_size,
                        .width = len,
                        .height = (f32)font_size
                };

                start_y = start_y + (font_size * 2);
        }
}

static bool _menuIsMouseOver(const Option* option) {
         return CheckCollisionPointRec(GetMousePosition(), option->rect_bounds);
}

static bool _menuOptionClick(const Option* option) {
        return (_menuIsMouseOver(option) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

#endif
