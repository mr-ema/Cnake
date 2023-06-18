#ifndef CNAKE_FOOD_H
#define CNAKE_FOOD_H

#include <stddef.h>
#include "raylib.h"
#include "grid.h"

typedef struct Food {
        Rectangle rec;
        bool active;

        Color color;
} Food;

static void spawn_food(Food*, const Grid);
static void draw_food(const Food*);

static void spawn_food(Food *food, const Grid grid) {
        if (!food->active) {
                food->active = true;

                food->rec.x = GetRandomValue(0, grid.columns - 1)  * grid.tile_size + grid.start_x;
                food->rec.y = GetRandomValue(0, grid.rows - 1) * grid.tile_size + grid.start_y;
        }
}

static void draw_food(const Food *food) {
        DrawRectangleRec(food->rec, food->color);
}

#endif
