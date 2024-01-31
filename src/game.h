#ifndef CNAKE_INIT_GAME_H
#define CNAKE_INIT_GAME_H

#include "raylib.h"
#include "types.h"
#include "config.h"
#include "snake.h"
#include "grid.h"
#include "food.h"
#include "collision.h"

typedef struct {
        GameState state;
        u32 screen_width;
        u32 screen_height;
        bool exit_game;
        Grid grid;
        u32 max_score;

        Snake snake;
        Food fruit;
} Game;

static Game init_game(void);
static void init_resources(Game* game);
static void restard_game(Game* game);
static void deinit_game(Game* game);

static Game init_game(void) {
        const u8 scale_tile_delta = 2;
        const u32 COLUMNS = (SCREEN_WIDTH - OFFSET_X) / TILE_SIZE;
        const u32 ROWS = (SCREEN_HEIGHT - OFFSET_Y) / TILE_SIZE;

        Game game = {
                .state = TITLE_SCREEN,
                .screen_width = SCREEN_WIDTH,
                .screen_height = SCREEN_HEIGHT,
                .exit_game = false,
                .max_score = ((ROWS * COLUMNS) - 1) / scale_tile_delta,
        };

        Grid grid = {
                .columns = COLUMNS,
                .rows = ROWS,
                .tile_size = TILE_SIZE,

                .start_x = (SCREEN_WIDTH - (COLUMNS * TILE_SIZE + OFFSET_X)) / 2 + OFFSET_X / 2,
                .start_y = (SCREEN_HEIGHT - (ROWS * TILE_SIZE + OFFSET_Y)) / 2 + OFFSET_Y / 2
        };

        Snake snake = {
                .head = (SnakeSegment){
                        .position = (Vector2){ grid.start_x, grid.start_y },
                        .color = HEAD_COLOR,
                },
                .speed_mode = NORMAL,
                ._speed = (Vector2){ (float)grid.tile_size, 0 },
                .size = (Vector2){ (float)grid.tile_size * scale_tile_delta, (float)grid.tile_size * scale_tile_delta },
                .len = 1,
                .allow_move = false,
        };

        for (u32 i = 0; i < CNAKE_LEN; i++) {
                snake.body[i].position = (Vector2){ 0.0f, 0.0f };
                snake.body[i].color = BODY_COLOR;
        }

        Food fruit = {
                .rec = (Rectangle){ -100.0f, 0.0f, (float)grid.tile_size * scale_tile_delta, (float)grid.tile_size * scale_tile_delta },
                .active = false,
                .color = FRUIT_COLOR,
        };

        game.snake = snake;
        game.fruit = fruit;
        game.grid = grid;

        return game;
}

static void init_resources(Game *game) {
        Sound crunch = LoadSound("assets/crunch.wav");

        game->snake.crunch_sound = crunch;
}

static void deinit_game(Game* game) {
        UnloadSound(game->snake.crunch_sound);
}

static void restard_game(Game* game) {
        game->snake.score = 0;
        game->snake.len = 1;
        game->snake.head.position = (Vector2){ game->grid.start_x + game->grid.tile_size, game->grid.start_y };
        game->snake._speed = (Vector2){ (float)game->grid.tile_size, 0 };
        game->snake.allow_move = false;

        game->fruit.active = false;
        game->state = PLAYING;
}

#endif
