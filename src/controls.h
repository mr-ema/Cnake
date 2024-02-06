#ifndef CNAKE_CONTROLS_H
#define CNAKE_CONTROLS_H

#include "config.h"
#include "raylib.h"
#include "types.h"

typedef enum ControlAction {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        PAUSE_GAME,
        GOBACK,
        TOTAL_ACTIONS
} ControlAction;

static int keybindings[TOTAL_ACTIONS] = {
    DEFAULT_KEY_MOVE_UP,
    DEFAULT_KEY_MOVE_DOWN,
    DEFAULT_KEY_MOVE_LEFT,
    DEFAULT_KEY_MOVE_RIGHT,
    DEFAULT_KEY_PAUSE_GAME,
    DEFAULT_KEY_GOBACK,
};


static void controlSet(ControlAction action, int key);
static int controlGet(ControlAction action);
static void controlReset(void);

void controlSet(ControlAction action, int key) {
        if (action >= 0 && action < TOTAL_ACTIONS) {
                keybindings[action] = key;
        }
}

static int controlGet(ControlAction action) {
        if (action >= 0 && action < TOTAL_ACTIONS) {
                return keybindings[action];
        }

        return -1;
}

static void controlReset(void) {
        for (int i = 0; i < TOTAL_ACTIONS; i++) {
                keybindings[i] = DEFAULT_KEY_MOVE_UP + i;
        }
}

#endif
