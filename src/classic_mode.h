#ifndef CNAKE_CLASSIC_MODE_GAME_H
#define CNAKE_CLASSIC_MODE_GAME_H

#include "config.h"
#include "raylib.h"
#include "game.h"
#include "snake.h"
#include "food.h"
#include "controls.h"

static void classicModeUpdate(Game* game);
static void classicModeRender(const Game* game);

static void classicModeUpdate(Game* game) {
        if (game->snake.len == CNAKE_LEN || game->snake.score == game->max_score) {
                game->state = WIN;
                return;
        } else if (IsKeyPressed(controlGet(PAUSE_GAME))) {
                game->state = MENU;
        }

        foodSpawnRandom(&game->fruit, &game->grid);

        if (checkSnakeSelfCollision(&game->snake) || checkSnakeWallCollision(&game->snake, &game->grid)) {
                game->state = GAME_OVER;
        } else if (checkSnakeFoodCollision(&game->snake, &game->fruit)) {
                snakeEat(&game->snake);
                game->fruit.active = false;
        }

        snakeUpdate(&game->snake);
}

static void classicModeRender(const Game* game) {
        ClearBackground(SCREEN_BACKGROUND);

        gridDraw(&game->grid);
        snakeDraw(&game->snake);

        // Draw Food
        DrawRectangleRec(game->fruit.rec, FRUIT_COLOR);

        DrawFPS(game->screen_width - 100, 20);
        DrawText(TextFormat("SCORE: %i", game->snake.score), 30, 20, 20, RAYWHITE);
}

#endif
