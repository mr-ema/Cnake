#ifndef CNAKE_GRID_H
#define CNAKE_GRID_H

#include "types.h"
#include "config.h"
#include "raylib.h"

typedef struct {
        u32 columns;
        u32 rows;
        u8 tile_size;

        f32 start_x;
        f32 start_y;
} Grid;

static void gridCenter(Grid* grid, u32 screen_width, u32 screen_height);
static void gridDraw(const Grid* grid);
static void gridDrawOnlyBorders(const Grid* grid);

static void gridDrawOnlyBorders(const Grid* grid) {
        DrawRectangleLines(
                grid->start_x,
                grid->start_y,
                grid->columns * grid->tile_size,
                grid->rows * grid->tile_size,
                GRID_BORDER_COLOR
        );
}

static void gridDraw(const Grid* grid) {
        for (u32 i = 0; i <= grid->columns; i++) {
                DrawLineV(
                        (Vector2){ grid->start_x + grid->tile_size * i, grid->start_y },
                        (Vector2){ grid->start_x + grid->tile_size * i, grid->start_y + grid->rows * grid->tile_size },
                        GRID_COLOR
                );
        }

        for (u32 i = 0; i <= grid->rows; i++) {
                DrawLineV(
                        (Vector2){ grid->start_x, grid->start_y + grid->tile_size * i },
                        (Vector2){ grid->start_x + grid->columns * grid->tile_size, grid->start_y + grid->tile_size * i },
                        GRID_COLOR
                );
        }
}

static void gridCenter(Grid* grid, u32 screen_width, u32 screen_height) {
        u32 grid_width = grid->columns * grid->tile_size;
        u32 grid_height = grid->rows * grid->tile_size;

        u32 offset_x = (screen_width - grid_width) / 2;
        u32 offset_y = (screen_height - grid_height) / 2;

        grid->start_x = (f32)offset_x;
        grid->start_y = (f32)offset_y;
}

#endif
