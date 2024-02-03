#include "grid.h"
#include "raylib.h"
#include "menu.h"
#include "config.h"
#include "game.h"
#include "title_screen.h"
#include "types.h"
#include "food.h"
#include "game_over.h"
#include "win.h"
#include "classic_mode.h"

static void updateGame(Game* game);
static void renderGame(Game* game);

int main(void) {
        Game game = gameInit();

        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(game.screen_width, game.screen_height, "Cnake");

                InitAudioDevice();
                gameResourcesInit(&game);

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

                                gridCenter(&game.grid, game.screen_width, game.screen_height);

                                f32 offset_diff_x = (f32)(game.grid.start_x - old_grid_start_x);
                                f32 offset_diff_y = (f32)(game.grid.start_y - old_grid_start_y);

                                game.fruit.rec.x += offset_diff_x;
                                game.fruit.rec.y += offset_diff_y;

                                game.snake.head.position.x += offset_diff_x;
                                game.snake.head.position.y += offset_diff_y;

                                for (u32 i = game.snake.len - 1; i > 0; i--) {
                                        game.snake.body[i].position.x += offset_diff_x;
                                        game.snake.body[i].position.y += offset_diff_y;
                                }
                        }

                        updateGame(&game);
                        renderGame(&game);
                }

                gameDeinit(&game);
                CloseAudioDevice();

        CloseWindow();
}

static void updateGame(Game* game) {
        switch (game->state) {
                case TITLE_SCREEN:
                        titleSceneUpdate(game);
                        break;
                case PLAYING:
                        classicModeUpdate(game);
                        break;
                case MENU:
                        menuUpdate(&game->state);
                        break;
                case GAME_OVER:
                        gameOverUpdate(game);
                        break;
                case RESTART:
                        gameRestard(game);
                        break;
                case WIN:
                        winSceneUpdate(game);
                        break;
                case EXIT_GAME:
                        game->exit_game = true;
                        break;
        }
}

static void renderGame(Game* game) {
        BeginDrawing();
                switch (game->state) {
                        case TITLE_SCREEN:
                                titleSceneRender(game->screen_width, game->screen_height, game);
                                break;
                        case PLAYING:
                                classicModeRender(game);
                                break;
                        case MENU:
                                menuRender();
                                break;
                        case GAME_OVER:
                                classicModeRender(game);
                                gameOverRender(game->screen_width, game->screen_height);
                                break;
                        case RESTART:
                                gameRestard(game);
                                break;
                        case WIN:
                                winSceneRender(game->screen_width, game->screen_height);
                                break;
                        case EXIT_GAME:
                                game->exit_game = true;
                                break;
                }
        EndDrawing();
}
