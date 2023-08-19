#ifndef CNAKE_GRID_H
#define CNAKE_GRID_H

#include "types.h"
#include "config.h"
#include "raylib.h"

typedef struct {
        u32 columns;
        u32 rows;
        u8 tile_size;

        float start_x;
        float start_y;
} Grid;

typedef enum {
        GRID_DEFAULT,
        GRID_ONLY_BORDERS,
} GridOptions;

// Grid functions
Grid init_grid();
static void handle_grid(const Grid* grid, GridOptions options);
static void draw_grid(const Grid* grid);
static void draw_grid_borders(const Grid* grid);

static void handle_grid(const Grid* grid, GridOptions options) {
        if (options == GRID_ONLY_BORDERS) {
                draw_grid_borders(grid);
        } else {
                draw_grid(grid);
        }
};

static void draw_grid_borders(const Grid* grid) {
        DrawRectangleLines(
                grid->start_x,
                grid->start_y,
                grid->columns * grid->tile_size,
                grid->rows * grid->tile_size,
                GRID_BORDER_COLOR
        );
}

static void draw_grid(const Grid* grid) {
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

#endif
