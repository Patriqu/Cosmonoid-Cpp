#include "Renderer.h"

Renderer::Renderer(int level, GameState* game_state)
    : screen(SDL_GetWindowSurface(SDL_GetWindowFromID(1))),
      color_bgd(),
      level(level),
      game_state(game_state),
      main_menu_view(new MainMenuView()),
      paddle_view(nullptr),
      ball_view(nullptr),
      bricks_view_level(nullptr),
      game_points_view(nullptr),
      bonus_view(nullptr),
      FPS(120),
      SKIP_TICKS(1000/*350*/ / FPS),
      sleep_time(),
      next_game_tick(GetTickCount())
{
    // create menu background with proper resolution
    const std::string h = std::to_string(screen->h);

    std::string temp = "img/background_";
    temp += h;
    temp += ".png";
    const char* ctemp = temp.c_str();

    bgd_surface = IMG_Load(ctemp);
}

Renderer::~Renderer()
{
    SDL_FreeSurface(screen);

    free(game_state);
    free(main_menu_view);
    free(paddle_view);
    free(ball_view);
    free(bricks_view_level);
    free(game_points_view);
    free(bonus_view);

    delete screen;
    delete game_state;
    delete main_menu_view;
    delete paddle_view;
    delete ball_view;
    delete bricks_view_level;
    delete game_points_view;
    delete bonus_view;
}

void Renderer::Render()
{
    // Control of FPS depends on display:
    next_game_tick += SKIP_TICKS;
    sleep_time = next_game_tick - GetTickCount();
    if( sleep_time >= 0 )
    {
        Sleep( sleep_time );
    }

    //// Draw background: ////
    SDL_BlitSurface(bgd_surface, nullptr, screen, nullptr);

    // Fill screen with one color
    const std::string color_name = main_menu_view->getBgdName();
    if (color_name == "no")
    {
        color_bgd = SDL_MapRGB(screen->format, 0, 0, 0);
        SDL_FillRect(screen, nullptr, color_bgd);
    }

    /* *** STATES *** */

    current_state = game_state->getCurrentState();

    if (current_state == "MAIN_MENU")
    {
        main_menu_view->renderMenu();
    }
        /* Change displayed level after win in previous (game state must be equal "NEXT_LEVEL") */
    else if (current_state == "NEXT_LEVEL")
    {
        // load next (up) displayed level
        level += 1;
        bricks_view_level->changeDisplayLevel(level);
    }

        /* *** PREPARING AFTER FIRST STARTING THE GAME *** */
    else if (current_state == "START_GAME")
    {
        onStartGame();
    }

    /* *** AFTER PLACING ALL OBJECTS AT SCREEN WITH CURRENT FRAME *** */
    if (current_state != "BEGIN_GAME" && current_state != "MAIN_MENU")
    {
        onBeginGame();
    }
}

void Renderer::onStartGame()
{
    // then create new instances of view classes
    paddle_view = new PaddleView();
    ball_view = new BallView();

    if (level != 1) level = 1;

    bricks_view_level = new BricksViewLevels(level);

    game_points_view = new GamePointsView();
    bonus_view = new BonusView();

    // After loaded starting data, change current game state to "Resume Game"
    game_state->changeGameState("RESUME_GAME");
}

void Renderer::onBeginGame()
{
    paddle_view->renderPaddle();
    ball_view->placeBall(0);

    if (current_state == "LOSE_GAME")
    {
        if (level != 1)
        {
            level = 1;
            bricks_view_level->changeDisplayLevel(level);
        }
    }

    bricks_view_level->placeAllBricks();
    game_points_view->placeAllPoints();

    bonus_view->renderBonus();
}
