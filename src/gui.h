#ifndef CNAKE_UI_H
#define CNAKE_UI_H

#include "raylib.h"
#include "types.h"

/*
typedef enum {
        IDLE = 0,
        HOVERED,
        PRESSED
} ButtonState;
*/

static bool CUILabelBtn(Rectangle bounds, const char* text, Color color, Color hover_color);

static bool CUILabelBtn(Rectangle bounds, const char* text, Color color, Color hover_color) {
        const Vector2 mouse_pos = GetMousePosition();
        const bool mouse_over = CheckCollisionPointRec(mouse_pos, bounds);
        const u8 font_size = 20;

        u16 text_width = MeasureText(text, font_size);
        f32 text_x = bounds.x + (bounds.width - text_width) / 2;
        f32 text_y = bounds.y + (bounds.height - font_size) / 2;


        if (mouse_over) {
                DrawText(text, text_x, text_y, font_size, hover_color);
        } else {
                DrawText(text, text_x, text_y, font_size, color);
        }

        return (mouse_over && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

#endif
