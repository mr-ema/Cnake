#ifndef CNAKE_COLLISION_H
#define CNAKE_COLLISION_H

#include "raylib.h"
#include "snake.h"
#include "food.h"

static bool check_snake_self_collision(const Snake*);
static bool check_snake_wall_collision(const Snake*, const Vector2, const Vector2);
static bool check_snake_food_collision(const Snake*, const Food*);

static bool check_snake_self_collision(const Snake *snake) {
        for (int i = 0; i < snake->len; i++) {
                if (snake->head.position.x == snake->body[i].position.x && snake->head.position.y == snake->body[i].position.y)
                        return true;
        }

        return false;
}

static bool check_snake_wall_collision(const Snake* snake, const Vector2 boundary_min, const Vector2 boundary_max) {
        u32 snake_x = snake->head.position.x;
        u32 snake_y = snake->head.position.y;

        if (snake_x + snake->size.x > boundary_max.x || snake_x < boundary_min.x || snake_y + snake->size.y > boundary_max.y || snake_y < boundary_min.y) {
                return true;
        }

        return false;
}

static bool check_snake_food_collision(const Snake *snake, const Food *food) {
        u32 snake_x = snake->head.position.x;
        u32 snake_y = snake->head.position.y;

        if (snake_x == food->rec.x && snake_y == food->rec.y) {
                return true;
        }

        return false;
}

#endif

