#include "raylib.h"
#include "math.h"

#include "types.h"
#include "food.h"
#include "collision.h"

// Configurations
#define TARGET_FPS 10
#define CNAKE_LEN 1024
#define TILE_SIZE (u8)30
#define OFFSET_X (float)200
#define OFFSET_Y (float)200

// Colors
#define GRIDCOLOR   (Color){ 30, 30, 30, 255 }
#define HEAD_COLOR  (Color){ 0, 150, 0, 255 }
#define BODY_COLOR  (Color){ 0, 100, 0, 255 }
#define FRUIT_COLOR (Color){ 150, 0, 0, 255 }


// Struct Definition
typedef enum GameState {
        TITLE_SCREEN,
        GAME_OVER,
        PAUSED,
        PLAYING,
        WIN,
        RESTART
} GameState;

 // Global Variables
static const u32 SCREEN_WIDTH = 1280;
static const u32 SCREEN_HEIGHT = 640;

static const u32 COLUMNS = (SCREEN_WIDTH - OFFSET_X) / TILE_SIZE;
static const u32 ROWS = (SCREEN_HEIGHT - OFFSET_Y) / TILE_SIZE;
static const u16 MAX_SCORE = (ROWS * COLUMNS) - 1;

static Grid grid;
static Vector2 BOUNDERY_MIN;
static Vector2 BOUNDERY_MAX;

static GameState game_state;
static u32 score;

static Food fruit;
static Snake snake;
static SnakeSegment snake_body[CNAKE_LEN] = { 0 };

// Audio
Sound crunch;

// Function Declaration
static void new_game(void);
static void update_game(void);
static void draw_game(void);
static void draw_win_text(void);
static void draw_game_over(u16 font_size, Color color);
static void draw_title_screen(u16 text_size, Color bg_color, Color text_color);


int main(void) {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cnake");
                InitAudioDevice();
                crunch = LoadSound("assets/crunch.wav");

                SetTargetFPS(TARGET_FPS);
                new_game();

                while (!WindowShouldClose()) {
                        if (IsKeyPressed(KEY_P)) {
                                game_state = game_state == PAUSED ? PLAYING : PAUSED;
                        }

                        if (IsKeyPressed(KEY_R)) { 
                                game_state = RESTART;
                                new_game();
                        }

                        if (game_state == PLAYING) { update_game(); }

                        draw_game();
                }

                UnloadSound(crunch);
                CloseAudioDevice();

        CloseWindow();
}

void new_game(void) {
        game_state = game_state == RESTART ? PLAYING : TITLE_SCREEN;
        score = 0;

        // Create a grid
        grid = (Grid) {
                .columns = COLUMNS,
                .rows = ROWS,
                .tile_size = TILE_SIZE,

                .start_x = (SCREEN_WIDTH - (COLUMNS * TILE_SIZE + OFFSET_X)) / 2 + OFFSET_X / 2,
                .start_y = (SCREEN_HEIGHT - (ROWS * TILE_SIZE + OFFSET_Y)) / 2 + OFFSET_Y / 2
        };

        // Set wall boundaries
        BOUNDERY_MIN = (Vector2){ grid.start_x, grid.start_y };
        BOUNDERY_MAX = (Vector2){ (SCREEN_WIDTH - OFFSET_X / 2), (SCREEN_HEIGHT - OFFSET_Y / 2) };

        snake = (Snake){
                .body = snake_body,
                .head = (SnakeSegment){ .color = HEAD_COLOR, .position = (Vector2){ grid.start_x, grid.start_y } },
                .speed = (Vector2){ grid.tile_size, 0 },
                .size = (Vector2){ grid.tile_size, grid.tile_size },
                .len = 1,
        };

        for (u32 i = 0; i < CNAKE_LEN; i++) {
                snake.body[i].position = (Vector2){ 0.0f, 0.0f };
                snake.body[i].color = BODY_COLOR;
        }

        fruit = (Food) {
                .rec = (Rectangle){ -100.0f, 0.0f, grid.tile_size, grid.tile_size },
                .color = FRUIT_COLOR,
                .active = false,
        };
}

void update_game(void) {
        move_snake(&snake, grid.tile_size);
        update_snake(&snake);
        spawn_food(&fruit, grid); 

        if (check_snake_self_collision(&snake) || check_snake_wall_collision(&snake, BOUNDERY_MIN, BOUNDERY_MAX)) {
                game_state = GAME_OVER;
        }

        if (check_snake_food_collision(&snake, &fruit)) {
                snake.body[snake.len].position = snake.body[snake.len - 1].position;
                snake.len += 1;

                score += 1;
                fruit.active = false;

                PlaySound(crunch);
        }
}

static void draw_title_screen(u16 title_size, Color bg_color, Color text_color) {
        ClearBackground(bg_color);

        DrawText("Press [Enter] To Start The Game!",
                SCREEN_WIDTH / 2 - MeasureText("Press [Enter] To Start The Game!", title_size) / 2,
                SCREEN_HEIGHT / 2 - title_size, title_size,
                text_color
        );
}

static void draw_game_over(u16 font_size, Color color) {
        DrawText("GAME OVER",
                SCREEN_WIDTH / 2 - MeasureText("GAME OVER", font_size) / 2,
                SCREEN_HEIGHT / 2 - font_size, font_size,
                color
        );

        DrawText("PRESS [R] TO RESTART",
                SCREEN_WIDTH / 2 - MeasureText("PRESS [R] TO RESTART", font_size * 0.35) / 2,
                SCREEN_HEIGHT / 2 + 10, font_size * 0.35,
                color 
        );
}

static void draw_win_text(void) {
        DrawText("You won the game!", SCREEN_WIDTH / 2 - MeasureText("You won the game!", 40) / 2, SCREEN_HEIGHT / 2 - 50, 40, RAYWHITE);
}

static void draw_game(void) {
        BeginDrawing();

                switch (game_state) {
                        case TITLE_SCREEN:
                                if (IsKeyPressed(KEY_ENTER)) { game_state = PLAYING; }
                                draw_title_screen(40, RAYWHITE, BLACK);
                                break;
                        case PAUSED:
                                DrawText("PAUSED", SCREEN_WIDTH/2 - MeasureText("PAUSED", 40)/2, SCREEN_HEIGHT/2 - 40, 40, RAYWHITE);
                                break;
                        case GAME_OVER:
                                if (game_state == GAME_OVER) { draw_game_over(60, RAYWHITE); }
                                break;
                        case WIN:
                                draw_win_text();
                                break;
                        default:
                                ClearBackground(BLACK);
                                DrawFPS(SCREEN_WIDTH - 100, 20);
                                draw_grid(&grid, GRIDCOLOR, GRIDCOLOR);

                                DrawText(TextFormat("SCORE: %i", score), 30, 20, 20, RAYWHITE);

                                draw_snake(&snake);
                                draw_food(&fruit);

                                // Stop the game before overflow
                                if (snake.len == CNAKE_LEN || score == MAX_SCORE) {
                                        game_state = WIN;
                                }
                                break;
                }

        EndDrawing();
}
