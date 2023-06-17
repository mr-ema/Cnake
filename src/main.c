#include "raylib.h"
#include "ztypes.h"

// TODO: Refactor this mess once the audio is working
// TODO: Make the snake speed more customizable
// TODO: Split the code into modules once the game is playable

#define CNAKE_LEN 1024
#define GRIDCOLOR (Color){ 40, 40, 40, 255 }


// Struct Definition
typedef enum GameState {
        STARTSCREEN,
        GAMEOVER,
        PAUSED,
        PLAYING,
        RESTART
} GameState;

typedef struct Grid {
        u32 width;
        u32 height;
        u16 start_x;
        u16 start_y;
} Grid;

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

static Grid grid = { 0 };

static Vector2 offset = { 0 };
static const u16 TILE_SIZE = 10;

static bool can_move = false;
static GameState game_state;

static Food fruit = { 0 };
static Snake snake[CNAKE_LEN] = { 0 };
static Vector2 snake_position[CNAKE_LEN] = { 0 };
static u32 seg_counter = 0;

// Textures
Texture2D title_screen_bg;

// Audio
Sound crunch;

// Function Declaration
static void load_assets(void);
static void unload_assets(void);
static void draw_title_screen(void);
static void init_game(void);
static void update_game(void);
static void draw_grid(void);
static void draw_game(void);


int main(void) {
        init_game();

        InitWindow(screen_width, screen_height, "Cnake");
        InitAudioDevice();
                
                load_assets();
                SetTargetFPS(60);

                while (!WindowShouldClose()) {
                        if (IsKeyPressed(KEY_P)) { game_state = game_state == PAUSED ? PLAYING : PAUSED; }
                        if (IsKeyPressed(KEY_R)) { 
                                game_state = RESTART;
                                init_game();
                        }

                        if (game_state == PLAYING) { update_game(); }

                        draw_game();
                }

                unload_assets();

        CloseWindow();
}

void init_game(void) {
        game_state = game_state == RESTART ? PLAYING : STARTSCREEN; // temporal way of restart the game
        seg_counter = 1;
        can_move = false;

        offset.x = (screen_width % TILE_SIZE) + padding;
        offset.y = (screen_height % TILE_SIZE) + padding;

        grid.width = (screen_width - offset.x) / TILE_SIZE;
        grid.height = (screen_height - offset.y) / TILE_SIZE;

        grid.start_x = (screen_width - (grid.width * TILE_SIZE + offset.x)) / 2 + offset.x / 2;
        grid.start_y = (screen_height - (grid.height * TILE_SIZE + offset.y)) / 2 + offset.y / 2;

        for (u32 i = 0; i < CNAKE_LEN; i++) {
                snake[i].position = (Vector2){ grid.start_x, grid.start_y };
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

                fruit.rec.x = GetRandomValue(0, grid.width - 1)  * TILE_SIZE + grid.start_x;
                fruit.rec.y = GetRandomValue(0, grid.height - 1) * TILE_SIZE + grid.start_y;
        }
        
        // Self collision
        for (int i = 1; i < seg_counter; i++) {
                if (snake[0].position.x == snake[i].position.x && snake[0].position.y == snake[i].position.y)
                        game_state = GAMEOVER;
        }

        // Hit wall
        if (snake[0].position.x + snake[0].size.x > (screen_width - offset.x / 2)  || snake[0].position.x < offset.x / 2 ||
            snake[0].position.y + snake[0].size.y > (screen_height - offset.y / 2) || snake[0].position.y < offset.y / 2) {
                game_state = GAMEOVER;
        }

        // Collision with fruit
        if (CheckCollisionPointRec(snake[0].position, fruit.rec)) {
                snake[seg_counter].position = snake_position[seg_counter - 1];
                PlaySound(crunch);

                seg_counter += 1;
                fruit.active = false;
        }

}

void load_assets(void) {
        title_screen_bg = LoadTexture("assets/snake.png");
        crunch = LoadSound("assets/crunch.wav");
}

void unload_assets(void) {
        UnloadTexture(title_screen_bg);
        UnloadSound(crunch);
        CloseAudioDevice();
}

void draw_title_screen() {
        // DrawTexture(start_bg, 0, 0, WHITE);
        DrawText("Press [Enter] To Start The Game!", screen_width/2 - MeasureText("Press [Enter] To Start The Game!", 40)/2, screen_height/2 - 40, 40, BLACK);
}

void draw_grid(void) {
        for (u32 i = 0; i <= grid.width; i++) {
                DrawLineV(
                        (Vector2){ grid.start_x + TILE_SIZE * i, grid.start_y },
                        (Vector2){ grid.start_x + TILE_SIZE * i, grid.start_y + grid.height * TILE_SIZE },
                        GRIDCOLOR
                );
        }

        for (u32 i = 0; i <= grid.height; i++) {
                DrawLineV(
                        (Vector2){ grid.start_x, grid.start_y + TILE_SIZE * i },
                        (Vector2){ grid.start_x + grid.width * TILE_SIZE, grid.start_y + TILE_SIZE * i },
                        GRIDCOLOR
                );
        }
}


void draw_game(void) {
        BeginDrawing();
                if (game_state == STARTSCREEN) {
                        ClearBackground(RAYWHITE);
                        if (IsKeyPressed(KEY_ENTER)) { game_state = PLAYING; }
                        draw_title_screen();
                } else {
                        ClearBackground(BLACK);
                        DrawFPS(screen_width - 100, 20);
                        draw_grid();

                        DrawText(TextFormat("SCORE: %i", seg_counter - 1), 30, 20, 20, RAYWHITE);

                        if (game_state == PAUSED) DrawText("PAUSED", screen_width/2 - MeasureText("PAUSED", 40)/2, screen_height/2 - 40, 40, RAYWHITE);

                        // Draw snake
                        for (int i = 0; i < seg_counter; i++) {
                                DrawRectangleV(snake[i].position, snake[i].size, snake[i].color);
                        }

                        // Draw fruit
                        DrawRectangleRec(fruit.rec, fruit.color);

                        // Stop the game before overflow
                        if (seg_counter == CNAKE_LEN) {
                                game_state = GAMEOVER;
                        }

                        if (game_state == GAMEOVER) {
                                DrawText("GAME OVER", screen_width/2 - MeasureText("GAME OVER", 40)/2, screen_height/2 - 40, 40, RAYWHITE);
                                DrawText("PRESS [R] TO RESTART", screen_width/2 - MeasureText("PRESS [R] TO RESTART", 20)/2, screen_height/2 + 10, 20, RAYWHITE);
                        }
                }
        EndDrawing();
}
