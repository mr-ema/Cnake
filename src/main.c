#include "grid.h"
#include "raylib.h"
#include "controls.h"
#include "menu.h"
#include "config.h"
#include "game.h"
#include "title_screen.h"
#include "types.h"
#include "food.h"
#include "collision.h"
#include "game_over.h"
#include "win.h"

static void handle_playing(Game* game);
static void update_game(Game* game);

int main(void) {
        Game game = init_game();

        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(game.screen_width, game.screen_height, "Cnake");

                InitAudioDevice();
                init_resources(&game);

                SetTargetFPS(TARGET_FPS);

                SetExitKey(KEY_NULL);
                while (!game.exit_game) {
                        if (WindowShouldClose()) {
                                game.state = EXIT_GAME;
                        } else if (IsWindowResized() && !IsWindowFullscreen()) {
                                game.screen_width = GetScreenWidth();
                                game.screen_height = GetScreenHeight();
                                
                                u32 old_grid_start_x = game.grid.start_x;
                                u32 old_grid_start_y = game.grid.start_y; 

                                recenter_grid(&game.grid, game.screen_width, game.screen_height);

                                float offset_diff_x = (float)(game.grid.start_x - old_grid_start_x);
                                float offset_diff_y = (float)(game.grid.start_y - old_grid_start_y);

                                game.fruit.rec.x += offset_diff_x;
                                game.fruit.rec.y += offset_diff_y;

                                game.snake.head.position.x += offset_diff_x;
                                game.snake.head.position.y += offset_diff_y;

                                for (u32 i = game.snake.len - 1; i > 0; i--) {
                                        game.snake.body[i].position.x += offset_diff_x;
                                        game.snake.body[i].position.y += offset_diff_y;
                                }
                        }

                        update_game(&game);
                }

                deinit_game(&game);
                CloseAudioDevice();

        CloseWindow();
}

static void update_game(Game* game) {
        switch (game->state) {
                case TITLE_SCREEN:
                        handle_title_screen(game->screen_width, game->screen_height, &game->state);
                        break;
                case PLAYING:
                        handle_playing(game);
                        break;
                case MENU:
                        handle_menu(&game->state);
                        break;
                case GAME_OVER:
                        handle_game_over(game->screen_width, game->screen_height, &game->state);
                        break;
                case RESTART:
                        restard_game(game);
                        break;
                case WIN:
                        handle_win_state(game->screen_width, game->screen_height, &game->state);
                        break;
                case EXIT_GAME:
                        game->exit_game = true;
                        break;
        }
}

static void handle_playing(Game* game) {
        if (game->snake.len == CNAKE_LEN || game->snake.score == game->max_score) {
                game->state = WIN;
                return;
        } else if (IsKeyPressed(get_keybinding(PAUSE_GAME))) {
                game->state = MENU;
        }

        BeginDrawing();
                ClearBackground(SCREEN_BACKGROUND);

                handle_grid(&game->grid, 0);
                handle_snake(&game->snake, &game->grid, &game->state);
                handle_food(&game->fruit, &game->state, &game->grid);
                handle_collitions(&game->snake, &game->fruit, &game->grid, &game->state);

                DrawFPS(game->screen_width - 100, 20);
                DrawText(TextFormat("SCORE: %i", game->snake.score), 30, 20, 20, RAYWHITE);
        EndDrawing();
}
