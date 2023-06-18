#ifndef CNAKE_SNAKE_H
#define CNAKE_SNAKE_H

#include <stddef.h>
#include "raylib.h"
#include "grid.h"

typedef struct SnakeSegment {
        Vector2 position;
        Color color;
} SnakeSegment;

typedef struct Snake {
        struct SnakeSegment head;
        struct SnakeSegment *body;
        
        Vector2 speed;
        Vector2 size;
        size_t len;
} Snake;

static void move_snake(Snake*, const float);
static void update_snake(Snake*);
static void draw_snake(const Snake*);

static void move_snake(Snake *snake, const float speed) {
        if (IsKeyPressed(KEY_J) && snake->speed.y != -speed) {
                snake->speed = (Vector2){ 0, speed };
        }
        else if (IsKeyPressed(KEY_K) && snake->speed.y != speed) {
                snake->speed = (Vector2){ 0, -speed };
        }
        else if (IsKeyPressed(KEY_H) && snake->speed.x != speed) {
                snake->speed = (Vector2){ -speed, 0 };
        }
        else if (IsKeyPressed(KEY_L) && snake->speed.x != -speed) {
                snake->speed = (Vector2){ speed, 0 };
        }

}

static void update_snake(Snake *snake) {
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
