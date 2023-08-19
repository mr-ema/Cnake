#ifndef CNAKE_CONTROLS_H
#define CNAKE_CONTROLS_H

#include "config.h"
#include "raylib.h"

typedef enum {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        PAUSE_GAME,
        GOBACK,
        TOTAL_ACTIONS
} ControlActions;

static int keybindings[TOTAL_ACTIONS];

void set_keybinding(ControlActions action, int key);
int get_keybinding(ControlActions action);
void reset_keybindings_to_defaults(void);

#endif
