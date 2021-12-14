#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "SDL_image.h"

#include "controllers/Timer.h"
#include "rules/Gamestate.h"

/* Rendering primary objects of the game: */
#include "view/PaddleView.h"
#include "view/BallView.h"

#include "gui/MainMenuView.h"
#include "gui/GameMenuView.h"
#include "gui/GamePointsView.h"

#include "view/BonusView.h"

/* Rendering of levels: */
#include "view/BricksViewLevels.h"

#include <windows.h>

class Renderer
{
public:
    Renderer(int level, GameState* game_state/*, SDL_Window* window, SDL_Texture* texture */);
    virtual ~Renderer();

    void Render();

private:
    void onStartGame();
    void onBeginGame();

    // Defs of variables:
    SDL_Surface* screen;
    /*SDL_Window* window;
    SDL_Texture* texture;*/

    Uint32 color_bgd;
    SDL_Surface* bgd_surface;

    int level;
    std::string current_state;

    GameState* game_state;
    MainMenuView* main_menu_view;

    PaddleView* paddle_view;
    BallView* ball_view;
    BricksViewLevels* bricks_view_level;
    GamePointsView* game_points_view;
    BonusView* bonus_view;

    const int FPS;
    const int SKIP_TICKS;
    int sleep_time;
    DWORD next_game_tick;

    bool is_window;
    bool is_full;

    bool is_screen_changed;
};

#endif // RENDERER_H
