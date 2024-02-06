#ifndef CNAKE_CLASSIC_MODE_GAME_H
#define CNAKE_CLASSIC_MODE_GAME_H

#include "config.h"
#include "raylib.h"
#include "game.h"
#include "grid.h"
#include "snake.h"
#include "food.h"
#include "controls.h"
#include "utils.h"

static void classicModeUpdate(Game* game);
static void classicModeRender(const Game* game);

static void _classicModeDrawApple(const Rectangle area);

static void classicModeUpdate(Game* game) {
        if (game->snake.len == CNAKE_LEN || game->snake.score == game->max_score) {
                game->state = WIN;
        } else if (IsKeyPressed(controlGet(PAUSE_GAME))) {
                game->state = MENU;
        } else {
                foodSpawnRandom(&game->fruit, &game->grid);

                if (checkSnakeSelfCollision(&game->snake) || checkSnakeWallCollision(&game->snake, &game->grid)) {
                        game->state = GAME_OVER;
                } else if (checkSnakeFoodCollision(&game->snake, &game->fruit)) {
                        snakeEat(&game->snake);
                        game->fruit.active = false;
                }

                snakeUpdate(&game->snake);
        }
}

static void classicModeRender(const Game* game) {
        ClearBackground(SCREEN_BACKGROUND);

        gridDraw(&game->grid);
        snakeDraw(&game->snake);

        // Draw Food
        _classicModeDrawApple(game->fruit.rec);

        DrawFPS(game->screen_width - 100, 20);
        DrawText(TextFormat("SCORE: %i", game->snake.score), 30, 20, 20, RAYWHITE);
}

static void _classicModeDrawApple(Rectangle area) {
        Rectangle original_area = { 0, 0, 1024, 1024 };

        Rectangle rectangles[] = {
                { 182.3f, 246.0f, 269.2f, 107.2f },
                { 587.7f, 246.0f, 269.2f, 107.2f },
                { 268.5f, 922.6f, 200.4f, 90.9f },
                { 570.3f, 922.6f, 200.4f, 90.9f },
                { 107.2f, 353.2f, 808.3f, 508.5f },
                { 165.8f, 861.8f, 691.1f, 60.8f },
                { 451.4f, 108.3f, 92.0f, 80.3f },
                { 524.3f, 13.0f, 92.0f, 119.7f },
        };
        Color colors[] = {
                MAROON, MAROON, MAROON, MAROON, MAROON, MAROON, GREEN, GREEN
        };

        // Calculate scaling factors for position and size
        const f32 scale_x = area.width / original_area.width;
        const f32 scale_y = area.height / original_area.height;
        usize len = sizeof(rectangles) / sizeof(rectangles[0]);

        for (usize i = 0; i < len; i++) {
                const Rectangle scale_rec = {
                        .x = area.x + (rectangles[i].x * scale_x),
                        .y = area.y + (rectangles[i].y * scale_y),
                        .width = (rectangles[i].width * scale_x),
                        .height = (rectangles[i].height * scale_y),
                };

                DrawRectangleRec(scale_rec, colors[i]);
        }
}

#endif
