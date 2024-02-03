#ifndef CNAKE_SNAKE_H
#define CNAKE_SNAKE_H

#include <stddef.h>
#include "config.h"
#include "controls.h"
#include "raylib.h"
#include "types.h"
#include "utils.h"

#define CNAKE_LEN (usize)(((SCREEN_WIDTH - OFFSET_X) / TILE_SIZE) * ((SCREEN_HEIGHT - OFFSET_Y) / TILE_SIZE) / TILE_SCALE_DELTA)

typedef enum {
        SLOW,
        NORMAL,
        FAST,
        BLAZINGLY_FAST
} SnakeSpeedMode;

typedef struct SnakeSegment {
        Vector2 position;
        Color color;
} SnakeSegment;

typedef struct {
        struct SnakeSegment head;
        struct SnakeSegment body[CNAKE_LEN];
        Sound crunch_sound;

        SnakeSpeedMode speed_mode;
        Vector2 _speed;
        Vector2 size;
        usize len;

        u32 score;
        bool allow_move;
} Snake;

static void snakeUpdate(Snake* snake);
static void snakeDraw(const Snake* snake);
static void snakeEat(Snake* snake);

static void _snakeMove(Snake* snake, f32 speed);
static u8 _snakeFrameInterval(Snake* snake);

static void snakeUpdate(Snake* snake) {
        static u8 frame_counter = 0;

        _snakeMove(snake, snake->size.x);
        if (frame_counter % _snakeFrameInterval(snake) == 0) {
                snake->body[0].position = snake->head.position;

                snake->head.position.x += snake->_speed.x;
                snake->head.position.y += snake->_speed.y;

                for (u32 i = snake->len - 1; i > 0; i--) {
                        snake->body[i].position = snake->body[i - 1].position;
                }

                snake->allow_move = true;
        }

        frame_counter = (frame_counter < MAX_VALUE(u8)) ? frame_counter + 1 : 0;
}

static void snakeDraw(const Snake* snake) {
        DrawRectangleV(snake->head.position, snake->size, snake->head.color);
        for (int i = 1; i < snake->len; i++) {
                DrawRectangleV(snake->body[i].position, snake->size, snake->body[i].color);
        }
}

static void snakeEat(Snake *snake) {
        PlaySound(snake->crunch_sound);
        snake->body[snake->len].position = snake->body[snake->len - 1].position;

        snake->score += 1;
        snake->len += 1;
}

static u8 _snakeFrameInterval(Snake* snake) {
        switch (snake->speed_mode) {
                case SLOW:
                        return 6;
                case NORMAL:
                        return 4;
                case FAST:
                        return 2;
                case BLAZINGLY_FAST:
                        return 1;
        }
}

static void _snakeMove(Snake* snake, f32 speed) {
        if (IsKeyPressed(controlGet(MOVE_DOWN)) && snake->_speed.y == 0 && snake->allow_move) {
                snake->_speed = (Vector2){ 0, speed };
                snake->allow_move = false;
        }
        else if (IsKeyPressed(controlGet(MOVE_UP)) && snake->_speed.y == 0 && snake->allow_move) {
                snake->_speed = (Vector2){ 0, -speed };
                snake->allow_move = false;
        }
        else if (IsKeyPressed(controlGet(MOVE_LEFT)) && snake->_speed.x == 0 && snake->allow_move) {
                snake->_speed = (Vector2){ -speed, 0 };
                snake->allow_move = false;
        }
        else if (IsKeyPressed(controlGet(MOVE_RIGHT)) && snake->_speed.x == 0 && snake->allow_move) {
                snake->_speed = (Vector2){ speed, 0 };
                snake->allow_move = false;
        }
}

#endif
