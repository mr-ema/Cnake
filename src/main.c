#include "raylib.h"
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

        InitWindow(game.screen_width, game.screen_height, "Cnake");
                InitAudioDevice();
                init_resources(&game);

                SetTargetFPS(TARGET_FPS);

                while (!WindowShouldClose()) {
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
                case PAUSED:
                        BeginDrawing();
                                DrawText("PAUSED", game->screen_width/2 - MeasureText("PAUSED", 40)/2, game->screen_height/2 - 40, 40, RAYWHITE);
                        EndDrawing();

                        if (IsKeyPressed(KEY_P)) {
                                game->state = (game->state == PAUSED) ? PLAYING : PAUSED;
                        }
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
                default:
                        handle_playing(game);
                        break;
        }
}

static void handle_playing(Game* game) {
        if (game->snake.len == CNAKE_LEN || game->snake.score == game->max_score) {
                game->state = WIN;
                return;
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

        if (IsKeyPressed(KEY_P)) {
                game->state = (game->state == PAUSED) ? PLAYING : PAUSED;
        }
}
