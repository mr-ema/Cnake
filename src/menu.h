#ifndef CNAKE_MENU_H
#define CNAKE_MENU_H

#include "config.h"
#include "raylib.h"
#include "controls.h"
#include "types.h"
#include "game.h"
#include "gui.h"

typedef enum MenuState {
        MAIN_MENU = 0,
        CONTROLS_MENU,
        CHANGE_KEY
} MenuState;

typedef struct Menu {
        GameState* game_state;
        MenuState state;
        ControlAction control;
} Menu;

static Menu menu = {};

static void menuUpdate(GameState* state);
static void menuRender(void);

static void _menuMainMenuDraw(void);
static void _menuControlsMenuDraw(void);
static void _menuChangeKeyUpdate(void);
static void _menuChangeKeyDraw(void);

static void menuUpdate(GameState* state) {
        menu.game_state = state;

        switch(menu.state) {
                case MAIN_MENU:
                        if (IsKeyPressed(controlGet(PAUSE_GAME))) {
                                *state = PLAYING;
                        }
                        break;
                case CONTROLS_MENU:
                        if (IsKeyPressed(controlGet(GOBACK))) {
                                menu.state = MAIN_MENU;
                        }
                        break;
                case CHANGE_KEY:
                        if (IsKeyPressed(controlGet(GOBACK))) {
                                menu.state = CONTROLS_MENU;
                        }
                        _menuChangeKeyUpdate();
                        break;
        }
}

static void menuRender(void) {
        switch(menu.state) {
                case MAIN_MENU:
                        _menuMainMenuDraw();
                        break;
                case CONTROLS_MENU:
                        _menuControlsMenuDraw();
                        break;
                case CHANGE_KEY:
                        _menuChangeKeyDraw();
                        break;
        }
}

static void _menuMainMenuDraw(void) {
        const f32 center_x = (f32)GetScreenWidth() / 2;
        const f32 center_y = (f32)GetScreenHeight() / 2;

        const f32 font_size = 20;
        const f32 btn_width = 200;

        const float btn_x = center_x - btn_width / 2;
        const float btn_y = center_y - font_size;

        Rectangle btn = {
                .x = center_x - btn_width / 2,
                .y = center_y - font_size,
                .width = btn_width,
                .height = font_size
        };

        ClearBackground(SCREEN_BACKGROUND);
        if (CUILabelBtn(btn, "Resume", RAYWHITE, GREEN)) {
                *menu.game_state = PLAYING;
        } btn.y += font_size * 2;
        if (CUILabelBtn(btn, "Controls", RAYWHITE, GREEN)) {
                menu.state = CONTROLS_MENU;
        } btn.y += font_size * 2;
        if (CUILabelBtn(btn, "Back To Title Screen", RAYWHITE, GREEN)) {
                *menu.game_state = TITLE_SCREEN;
        } btn.y += font_size * 2;
        if (CUILabelBtn(btn, "Exit", RAYWHITE, GREEN)) {
                *menu.game_state = EXIT_GAME;
        }
}

static void _menuControlsMenuDraw(void) {
        const f32 center_x = (f32)GetScreenWidth() / 2;
        const f32 center_y = (f32)GetScreenHeight() / 2;

        const f32 font_size = 20;
        const f32 btn_width = 200;

        Rectangle btn = {
                .x = center_x - btn_width / 2,
                .y = center_y - font_size,
                .width = btn_width,
                .height = font_size
        };

        ClearBackground(SCREEN_BACKGROUND);
        if (CUILabelBtn(btn, "UP", RAYWHITE, GREEN)) {
                menu.control = MOVE_UP;
                menu.state = CHANGE_KEY;
        } btn.y += font_size * 2;
        if (CUILabelBtn(btn, "DOWN", RAYWHITE, GREEN)) {
                menu.control = MOVE_DOWN;
                menu.state = CHANGE_KEY;
        } btn.y += font_size * 2;
        if (CUILabelBtn(btn, "RIGTH", RAYWHITE, GREEN)) {
                menu.control = MOVE_RIGHT;
                menu.state = CHANGE_KEY;
        } btn.y += font_size * 2;
        if (CUILabelBtn(btn, "LEFT", RAYWHITE, GREEN)) {
                menu.control = MOVE_LEFT;
                menu.state = CHANGE_KEY;
        }
}

static void _menuChangeKeyUpdate(void) {
        static int last_key = 0;
        if (last_key == 0) {
                last_key = controlGet(menu.control);
        }

        int temp_key = GetKeyPressed();
        if (IsKeyPressed(controlGet(GOBACK))) {
                menu.state = CONTROLS_MENU;
                controlSet(menu.control, last_key);
                last_key = 0;
        } else if (IsKeyPressed(KEY_ENTER)) {
                menu.state = CONTROLS_MENU;
                last_key = 0;
        } else if (temp_key != KEY_NULL) {
                controlSet(menu.control, temp_key);
        }
}

static void _menuChangeKeyDraw(void) {
        const u8 font_size = 30;
        const Vector2 center = { .x = (f32)GetScreenWidth() / 2, .y = (f32)GetScreenHeight() / 2 };
        const Color color = RAYWHITE;
        const char* feedback = "[PRESS ENTER TO SET NEW KEY]";

        int key = controlGet(menu.control);

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

#endif
