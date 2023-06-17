#ifndef CNAKE_GRID_H
#define CNAKE_GRID_H

#include "types.h"
#include "raylib.h"

typedef struct Grid {
        u32 columns;
        u32 rows;
        u8 tile_size;

        u16 start_x;
        u16 start_y;
} Grid;

// Grid functions
static void draw_grid(const Grid*, const Color, const Color);

static void draw_grid(const Grid* grid, Color color_x, Color color_y) {
        for (u32 i = 0; i <= grid->columns; i++) {
                DrawLineV(
                        (Vector2){ grid->start_x + grid->tile_size * i, grid->start_y },
                        (Vector2){ grid->start_x + grid->tile_size * i, grid->start_y + grid->rows * grid->tile_size },
                        color_y
                );
        }

        for (u32 i = 0; i <= grid->rows; i++) {
                DrawLineV(
                        (Vector2){ grid->start_x, grid->start_y + grid->tile_size * i },
                        (Vector2){ grid->start_x + grid->columns * grid->tile_size, grid->start_y + grid->tile_size * i },
                        color_x
                );
        }
}

#endif
