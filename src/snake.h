#ifndef CNAKE_SNAKE_H
#define CNAKE_SNAKE_H

#include <stddef.h>
#include "config.h"
#include "controls.h"
#include "raylib.h"
#include "grid.h"
#include "types.h"

typedef struct SnakeSegment {
        Vector2 position;
        Color color;
} SnakeSegment;

typedef struct {
        struct SnakeSegment head;
        struct SnakeSegment body[CNAKE_LEN];
        Sound crunch_sound;
        
        Vector2 speed;
        Vector2 size;
        size_t len;

        u32 score;
        bool allow_move;
} Snake;

static void handle_snake(Snake* snake, const Grid* grid, GameState* state);
static void move_snake(Snake* snake, float speed);
static void update_snake(Snake* snake);
static void draw_snake(const Snake* snake);
static u8 frame_counter = 0;

static void handle_snake(Snake* snake, const Grid* grid, GameState* state) {
        move_snake(snake, grid->tile_size);
        if (frame_counter % FRAME_UPDATE_INTERVAL == 0) {
                update_snake(snake);
                snake->allow_move = true;
        }

        draw_snake(snake);

        frame_counter = (frame_counter < MAX_U8) ? frame_counter + 1 : 0;
}

static void move_snake(Snake* snake, float speed) {
        if (IsKeyPressed(get_keybinding(MOVE_DOWN)) && snake->speed.y == 0 && snake->allow_move) {
                snake->speed = (Vector2){ 0, speed };
                snake->allow_move = false;
        }
        else if (IsKeyPressed(get_keybinding(MOVE_UP)) && snake->speed.y == 0 && snake->allow_move) {
                snake->speed = (Vector2){ 0, -speed };
                snake->allow_move = false;
        }
        else if (IsKeyPressed(get_keybinding(MOVE_LEFT)) && snake->speed.x == 0 && snake->allow_move) {
                snake->speed = (Vector2){ -speed, 0 };
                snake->allow_move = false;
        }
        else if (IsKeyPressed(get_keybinding(MOVE_RIGHT)) && snake->speed.x == 0 && snake->allow_move) {
                snake->speed = (Vector2){ speed, 0 };
                snake->allow_move = false;
        }
}

static void update_snake(Snake* snake) {
        snake->body[0].position = snake->head.position;

        snake->head.position.x += snake->speed.x;
        snake->head.position.y += snake->speed.y;

        for (u32 i = snake->len - 1; i > 0; i--)
                snake->body[i].position = snake->body[i - 1].position;
}

static void draw_snake(const Snake* snake) {
        DrawRectangleV(snake->head.position, snake->size, snake->head.color);
        for (int i = 1; i < snake->len; i++) {
                DrawRectangleV(snake->body[i].position, snake->size, snake->body[i].color);
        }
}

#endif
