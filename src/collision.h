#ifndef CNAKE_COLLISION_H
#define CNAKE_COLLISION_H

#include "raylib.h"
#include "snake.h"
#include "food.h"
#include "types.h"

typedef struct {
        Snake* snake;
        Food* food;
        Grid* grid;
        Vector2 wall_min;
        Vector2 wall_max;
} CollisionSystem;

static bool checkSnakeSelfCollision(const Snake* snake);
static bool checkSnakeWallCollision(const Snake* snake, const Grid* grid);
static bool checkSnakeFoodCollision(const Snake* snake, const Food* fruit);

static bool checkSnakeSelfCollision(const Snake* snake) {
        for (int i = 0; i < snake->len; i++) {
                if (snake->head.position.x == snake->body[i].position.x && snake->head.position.y == snake->body[i].position.y)
                        return true;
        }

        return false;
}

static bool checkSnakeWallCollision(const Snake* snake, const Grid* grid) {
        Vector2 boundary_min = {
                .x = grid->start_x,
                .y = grid->start_y
        };

        Vector2 boundary_max = {
                .x = grid->start_x + grid->tile_size * grid->columns,
                .y = grid->start_y + grid->tile_size * grid->rows
        };

        u32 snake_x = snake->head.position.x;
        u32 snake_y = snake->head.position.y;

        if (snake_x + snake->size.x > boundary_max.x || snake_x < boundary_min.x ||
            snake_y + snake->size.y > boundary_max.y || snake_y < boundary_min.y
        ) {
                return true;
        }

        return false;
}

static bool checkSnakeFoodCollision(const Snake* snake, const Food* fruit) {
        if (CheckCollisionPointRec(snake->head.position, fruit->rec)) {
                return true;
        }

        return false;
}

#endif

