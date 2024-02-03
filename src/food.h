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

static void foodSpawnRandom(Food* fruit, const Grid* grid);

static void foodSpawnRandom(Food *food, const Grid* grid) {
        if (!food->active) {
                food->active = true;
                u8 tile_size = grid->tile_size;
                f32 max_x = grid->start_x + (grid->columns * tile_size) - food->rec.width;
                f32 max_y = grid->start_y + (grid->rows * tile_size) - food->rec.height;

                food->rec.x = tile_size * (GetRandomValue(grid->start_x / tile_size, max_x / tile_size));
                food->rec.y = tile_size * (GetRandomValue(grid->start_y / tile_size, max_y / tile_size));
        }
}

#endif
