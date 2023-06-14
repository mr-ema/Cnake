#include "raylib.h"
#include "ztypes.h"

#define CNAKE_LEN 1024
#define GRIDCOLOR (Color){ 40, 40, 40, 255 }


// Struct Definition
typedef struct Snake {
        Vector2 position;
        Vector2 size;
        Vector2 speed;
        Color color;
} Snake;

typedef struct Food {
        Rectangle rec;
        bool active;
        Color color;
} Food;

 // Global Variables
static const u32 screen_width = 1280;
static const u32 screen_height = 640;
static const u32 padding = 200;

static u32 grid_width;
static u32 grid_height;

static u16 start_x;
static u16 start_y;

static Vector2 offset = { 0 };
static const u16 TILE_SIZE = 10;

static bool paused = false;
static bool game_over = false;
static bool can_move = false;


static Food fruit = { 0 };
static Snake snake[CNAKE_LEN] = { 0 };
static Vector2 snake_position[CNAKE_LEN] = { 0 };
static u32 seg_counter = 0;

 // Function Declaration
static void init_game(void);
static void update_game(void);
static void draw_grid(void);
static void draw_game(void);


int main(void) {
        init_game();

        InitWindow(screen_width, screen_height, "Cnake");
                SetTargetFPS(60);
                while (!WindowShouldClose()) {
                        if (IsKeyPressed(KEY_P)) { paused = !paused; }
                        if (IsKeyPressed(KEY_R)) { init_game(); }

                        if (!paused && !game_over) { update_game(); }

                        draw_game();
                }
        CloseWindow();
}

void init_game(void) {
        game_over = false;
        paused = false;

        seg_counter = 1;
        can_move = false;

        offset.x = (screen_width % TILE_SIZE) + padding;
        offset.y = (screen_height % TILE_SIZE) + padding;

        grid_width = (screen_width - offset.x) / TILE_SIZE;
        grid_height = (screen_height - offset.y) / TILE_SIZE;

        start_x = (screen_width - (grid_width * TILE_SIZE + offset.x)) / 2 + offset.x / 2;
        start_y = (screen_height - (grid_height * TILE_SIZE + offset.y)) / 2 + offset.y / 2;

        for (u32 i = 0; i < CNAKE_LEN; i++) {
                snake[i].position = (Vector2){ start_x, start_y };
                snake[i].speed = (Vector2){ TILE_SIZE, 0 };
                snake[i].size = (Vector2){ TILE_SIZE, TILE_SIZE };
                snake[i].color = DARKGREEN;

                snake_position[i] = (Vector2){ 0.0f, 0.0f };
        } snake[0].color = GREEN;

        fruit.rec = (Rectangle){ 0.0f, 0.0f, TILE_SIZE, TILE_SIZE };
        fruit.color = BLUE;
        fruit.active = false;
}

void move_snake(void) {
        if (IsKeyPressed(KEY_J) && (snake[0].speed.y == 0) && can_move) {
                snake[0].speed = (Vector2){ 0, TILE_SIZE };
                can_move = false;
        }
        if (IsKeyPressed(KEY_K) && (snake[0].speed.y == 0) && can_move) {
                snake[0].speed = (Vector2){ 0, -TILE_SIZE };
                can_move = false;
        }
        if (IsKeyPressed(KEY_H) && (snake[0].speed.x == 0) && can_move) {
                snake[0].speed = (Vector2){ -TILE_SIZE, 0 };
                can_move = false;
        }
        if (IsKeyPressed(KEY_L) && (snake[0].speed.x== 0) && can_move) {
                snake[0].speed = (Vector2){ TILE_SIZE, 0 };
                can_move = false;
        }
}

void update_game(void) {
        move_snake();

        for (u32 i = 0; i < seg_counter; i++)
                snake_position[i] = snake[i].position;

        snake[0].position.x += snake[0].speed.x;
        snake[0].position.y += snake[0].speed.y;
        can_move = true;

        for (u32 i = 1; i < seg_counter; i++)
                snake[i].position = snake_position[i - 1];

        if (!fruit.active) {
                fruit.active = true;

                fruit.rec.x = GetRandomValue(0, grid_width - 1)  * TILE_SIZE + start_x;
                fruit.rec.y = GetRandomValue(0, grid_height - 1) * TILE_SIZE + start_y;
        }
        
        // Self collision
        for (int i = 1; i < seg_counter; i++) {
                if (snake[0].position.x == snake[i].position.x && snake[0].position.y == snake[i].position.y)
                        game_over = true;
        }

        // Hit wall
        if (snake[0].position.x + snake[0].size.x > (screen_width - offset.x / 2)  || snake[0].position.x < offset.x / 2 ||
            snake[0].position.y + snake[0].size.y > (screen_height - offset.y / 2) || snake[0].position.y < offset.y / 2) {
                game_over = true;
        }

        // Collision with fruit
        if (CheckCollisionPointRec(snake[0].position, fruit.rec)) {
                snake[seg_counter].position = snake_position[seg_counter - 1];

                seg_counter += 1;
                fruit.active = false;
        }

}

void draw_grid(void) {
        for (u32 i = 0; i <= grid_width; i++) {
                DrawLineV(
                        (Vector2){ start_x + TILE_SIZE * i, start_y },
                        (Vector2){ start_x + TILE_SIZE * i, start_y + grid_height * TILE_SIZE },
                        GRIDCOLOR
                );
        }

        for (u32 i = 0; i <= grid_height; i++) {
                DrawLineV(
                        (Vector2){ start_x, start_y + TILE_SIZE * i },
                        (Vector2){ start_x + grid_width * TILE_SIZE, start_y + TILE_SIZE * i },
                        GRIDCOLOR
                );
        }
}

void draw_game(void) {
        BeginDrawing();
                ClearBackground(BLACK);

                DrawFPS(screen_width - 100, 20);
                draw_grid();

                DrawText(TextFormat("SCORE: %i", seg_counter - 1), 30, 20, 20, RAYWHITE);

                if (paused) DrawText("PAUSED", screen_width/2 - MeasureText("PAUSED", 40)/2, screen_height/2 - 40, 40, RAYWHITE);

                // Draw snake
                for (int i = 0; i < seg_counter; i++) {
                        DrawRectangleV(snake[i].position, snake[i].size, snake[i].color);
                }

                // Draw fruit
                DrawRectangleRec(fruit.rec, fruit.color);

                // Stop the game before overflow
                if (seg_counter == CNAKE_LEN) game_over = true;

                if (game_over) {
                        DrawText("GAME OVER", screen_width/2 - MeasureText("GAME OVER", 40)/2, screen_height/2 - 40, 40, RAYWHITE);
                        DrawText("PRESS [R] TO RESTARD", screen_width/2 - MeasureText("PRESS [R] TO RESTARD", 20)/2, screen_height/2 + 10, 20, RAYWHITE);
                }
        EndDrawing();
}
