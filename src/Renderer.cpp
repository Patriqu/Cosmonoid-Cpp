#include "Renderer.h"

Renderer:: Renderer( int level, GameState* game_state, SDL_Window* window/*, SDL_Texture* texture */ )
    : screen ( SDL_GetWindowSurface(SDL_GetWindowFromID(1)) ),
    window ( SDL_GetWindowFromID(1) ),
    texture ( texture ),
    color_bgd ( SDL_MapRGB( screen->format, 255, 255, 255) ),
    level ( level ),
    current_state ( "" ),
    game_state ( game_state ),
    main_menu_view ( new MainMenuView() ),
    paddle_view ( NULL ),
    ball_view ( NULL ),
    bricks_view_level ( NULL ),
    game_points_view ( NULL ),
    bonus_view ( NULL ),
    FPS ( 240 /*120*/ ),
    SKIP_TICKS ( 1000/*350*/ / FPS ),
    sleep_time ( 0 ),
    next_game_tick ( GetTickCount() ),
    is_window (true),
    is_full (false),
    is_screen_changed (false)
{
    // create menu background with proper resolution
    int i = screen->h;
    std:: string tmp;
    sprintf((char*)tmp.c_str(), "%d", i);
    std:: string h = tmp.c_str();

    std:: string temp = "img/background_";
    temp += h;
    temp += ".png";
    const char* ctemp = temp.c_str();

    bgd_surface = IMG_Load( ctemp );
}

Renderer:: ~Renderer()
{
    SDL_FreeSurface ( screen );

    free ( game_state );
    free ( main_menu_view );
    free ( paddle_view );
    free ( ball_view );
    free ( bricks_view_level );
    free ( game_points_view );
    free ( bonus_view );

    delete screen;
    delete game_state;
    delete main_menu_view;
    delete paddle_view;
    delete ball_view;
    delete bricks_view_level;
    delete game_points_view;
    delete bonus_view;
}

void Renderer:: Render()
{
    // Control of FPS depends from display:
    /*
    next_game_tick += SKIP_TICKS;
    sleep_time = next_game_tick - GetTickCount();
    if( sleep_time >= 0 )
    {
        Sleep( sleep_time );
        //SDL_Delay(2);
    }
    */


    //screen = SDL_GetWindowSurface(SDL_GetWindowFromID(1));

    //// Draw background: ////
    SDL_BlitSurface( bgd_surface, 0, screen, NULL );

    // Fill screen with one color
    std:: string color_name = main_menu_view -> getBgdName();
    if ( color_name == "no" )
    {
        color_bgd = SDL_MapRGB( screen->format, 0, 0, 0);
        SDL_FillRect( screen, 0, color_bgd );
    }
    //else if ( color_name == "yes" )
    //{
    //    color_bgd = SDL_MapRGB( screen->format, 0, 0, 0);
    //    SDL_FillRect( screen, 0, color_bgd );
    //}


    // Check whether change screen mode
    /*
    std:: string screen_name = main_menu_view -> getScreenModeName();
    if ( is_window == false && screen_name == "window" )
    {
        if (is_full == true)
            is_full = false;
        is_window = true;

        //SDL_Window* window;
        SDL_Event event;

        try
        {
            //// NOT WORKING PROPERLY - CRASH AFTER SELECT THE NEW GAME - I DON'T KNOW WHY: ////
            //SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP );

            //SDL_DestroyTexture(SDL_Get);

            //is_screen_changed = true;

            //SDL_FillRect( screen, 0, color_bgd );
        }
        catch(std::string obj)
        {
            obj = "Nie zmieniono trybu wyœwietlania ekranu";
            throw obj;
        }

    }
    else if ( is_full == false && screen_name == "full" )
    {
        if (is_window == true)
            is_window = false;
        is_full = true;

        try
        {
            // SDL_FillRect( screen, 0, color_bgd );
        }
        catch(std::string obj)
        {
            obj = "Nie zmieniono trybu wyœwietlania ekranu";
            throw obj;
        }
    }
    */

    // Get game state in current frame
    current_state = game_state -> getCurrentState();

    /* *** MENU STATE *** */

    if ( current_state == "MAIN_MENU" )
    {
        main_menu_view -> renderMenu();
    }
    /* Change displayed level after win in previous (game state must be equal "NEXT_LEVEL") */
    else if ( current_state == "NEXT_LEVEL" )
    {
        // load next (up) displayed level
        level += 1;
        bricks_view_level -> changeDisplayLevel( level );
    }

    /* *** PREPARING AFTER FIRST STARTING THE GAME *** */
    else if ( current_state == "START_GAME" )
    {
        // then create new instances of view classes
        paddle_view = new PaddleView();
        ball_view = new BallView();

        if ( level != 1 )
        {
            level = 1;
        }
        bricks_view_level = new BricksViewLevels( level );

        game_points_view = new GamePointsView();
        bonus_view = new BonusView();

        // After loaded starting data, change current game state to "Resume Game"
        game_state -> changeGameState( "RESUME_GAME" );
    }

    /* *** AFTER PLACING ALL OBJECTS AT SCREEN WITH CURRENT FRAME *** */
    // else if ( current_state == "RESUME_GAME" || current_state == "WIN_GAME" || current_state == "LOSE_GAME" )
    if ( current_state != "BEGIN_GAME" && current_state != "MAIN_MENU" )
    {
        // Place Paddle and Ball at screen:
        paddle_view -> placePaddle();
        ball_view -> placeBall(0);

        if ( current_state == "LOSE_GAME" )
        {
            if ( level != 1 )
            {
                level = 1;
                bricks_view_level -> changeDisplayLevel( level );
            }
        }

        // Place all bricks of choised level:
        bricks_view_level -> placeAllBricks();

        // Place all scores, lives and current level at top of screen:
        game_points_view -> placeAllPoints();

        // Render if bonus is now available:
        bonus_view -> renderBonus();

    }

}

bool Renderer:: isScreenChanged()
{
    return is_screen_changed;
}

void Renderer:: clearScreenChanged()
{
    is_screen_changed = false;
}
