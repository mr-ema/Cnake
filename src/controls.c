#include "config.h"
#include "raylib.h"
#include "controls.h"

// Array to store keybindings
static int keybindings[TOTAL_ACTIONS] = {
    DEFAULT_KEY_MOVE_UP,
    DEFAULT_KEY_MOVE_DOWN,
    DEFAULT_KEY_MOVE_LEFT,
    DEFAULT_KEY_MOVE_RIGHT,
    DEFAULT_KEY_PAUSE_GAME,
    DEFAULT_KEY_GOBACK,
};

void set_keybinding(ControlActions action, int key) {
        if (action >= 0 && action < TOTAL_ACTIONS) {
                keybindings[action] = key;
        }
}

int get_keybinding(ControlActions action) {
        if (action >= 0 && action < TOTAL_ACTIONS) {
                return keybindings[action];
        }

        return -1;
}

void reset_keybindings_to_defaults(void) {
        for (int i = 0; i < TOTAL_ACTIONS; i++) {
                keybindings[i] = DEFAULT_KEY_MOVE_UP + i;
        }
}
