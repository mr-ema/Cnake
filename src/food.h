#ifndef CNAKE_FOOD_H
#define CNAKE_FOOD_H

#include <stddef.h>
#include "raylib.h"
#include "grid.h"
#include "types.h"

typedef struct Food {
        Rectangle rec;
        bool active;

        Color color;
} Food;

static void handle_food(Food* fruit, GameState* state, const Grid* grid);
static void spawn_food(Food* fruit, const Grid* grid);
static void draw_food(const Food* fruit);

static void handle_food(Food* food, GameState* state, const Grid* grid) {
        spawn_food(food, grid);
        draw_food(food);
}

static void spawn_food(Food *food, const Grid* grid) {
        if (!food->active) {
                food->active = true;
                u8 tile_size = grid->tile_size;
                float max_x = grid->start_x + (grid->columns * tile_size) - food->rec.width;
                float max_y = grid->start_y + (grid->rows * tile_size) - food->rec.height;

                food->rec.x = tile_size * (GetRandomValue(grid->start_x / tile_size, max_x / tile_size));
                food->rec.y = tile_size * (GetRandomValue(grid->start_y / tile_size, max_y / tile_size));
        }
}

static void draw_food(const Food *food) {
        DrawRectangleRec(food->rec, food->color);
}

#endif
