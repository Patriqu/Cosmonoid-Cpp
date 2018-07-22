/**
@file main.cpp
*/

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <windows.h>
//#include <math.h>
#include <ctime>
#include <map>

#include <iostream>
#include <fstream>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Timer.h"
#include "GameState.h"
#include "UpdateGame.h"
#include "Renderer.h"

using namespace rapidxml;

int main ( int argc, char** argv )
{
    //// READ CONFIG DATAS: ////
    bool is_fullscreen = false;
    int width;
    int height;

    rapidxml::file<> xmlFile("text/config.xml");

    xml_document <> dokument;
    try {
        dokument.parse < 0/*parse_validate_closing_tags*/ >( xmlFile.data() );
    } catch( parse_error p ) {
        p.what();
    }

    xml_node <> * korzen = dokument.first_node("arkanoid");

    korzen = korzen->first_node("config");
    korzen = korzen->first_node("display");
    korzen = korzen->first_node("fullscreen");

    // CHECK SCREEN MODE (FULLSCREEN OR WINDOW):
    std::string str_full(korzen->value());
    if ( str_full == "true" )
        is_fullscreen = true;
    else
        is_fullscreen = false;

    std::cout << "Fullscreen: " << korzen->value() << std::endl;

    // CHECK SCREEN WIDTH:
    korzen = korzen->next_sibling("width");

    std::string str(korzen->value());
    width = atoi( str.c_str() );
    std::cout << "Width: " << width << std::endl;

    // CHECK SCREEN HEIGHT:
    korzen = korzen->next_sibling("height");

    std::string str_2(korzen->value());
    height = atoi( str_2.c_str() );
    std::cout << "Height: " << height << std::endl << std::endl;

    dokument.clear();


    //// Define a vector of velocities of context screen for objects ////
    std::map<std::string, int> surf_nbs;
    surf_nbs["width"] = 640;
    surf_nbs["height"] = 480;

    //// initialization of SDL ////
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    //// create a new window ////
    SDL_Window* window;
    SDL_Renderer* sdl_renderer;

    //// Initialize screen ////
    if ( is_fullscreen == true )
    {
        if (! (window = SDL_CreateWindow( "Simple Arkanoid - SDL2 v0.56", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/ ) ))
                                                return -1;

        //SDL_SetWindowSize(window, width, height);
        //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    }
    else if ( is_fullscreen == false )
    {
        if (! (window = SDL_CreateWindow( "Simple Arkanoid - SDL2 v0.56", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI ) ))
                                                return -1;
    }

    //// set icon at taskbar ////
    SDL_Surface* icon = IMG_Load( "img/icon.png" );
    SDL_SetWindowIcon( window, icon );

    if (! ( sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ) )
        return -1;

    if ( is_fullscreen == true )
        SDL_RenderSetLogicalSize(sdl_renderer, width, height);

    SDL_Texture* sdl_texture = SDL_CreateTexture(sdl_renderer,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               width, height);

    SDL_Surface* screen_surface = SDL_GetWindowSurface( window );

    SDL_FillRect( screen_surface, 0, SDL_MapRGB( screen_surface->format, 255, 255, 255 ) );

    //// Initialise TTF ////
    if( TTF_Init() == -1 ) { return -1; }

    // open 44.1KHz, signed 16bit, system byte order,
    // stereo audio, using 1024 byte chunks
    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(2);
    }


    /* **************** program main loop *************** */

    //// Basic definitions of variables that used in main loop ////
    bool done = false;
    const Uint8* keystate = SDL_GetKeyboardState( NULL );

    //// Starting level ////
    const int LEVEL = 1;

    //// Def of state of game, at start default state is "Begin game" ////
    GameState game_state;

    //// Defs of program's main structures ////
    UpdateGame* update_game = new UpdateGame( &game_state, /*surf_nbs,*/ keystate, LEVEL );
    Renderer* renderer = new Renderer( LEVEL, &game_state, window /*, sdl_texture */ );


    //Keep track of the frame count
    int frame = 0;
    //Timer used to calculate the frames per second
    Timer fps;
    //Timer used to update the caption
    Timer update;

    //const int MAX_FPS = 60;
    //const int MIN_FPS = 15;
    //const int UPDATE_INTERVAL = (1.0 / MAX_FPS) * 1000;
    //const float MAX_CYCLES_PER_FRAME = MAX_FPS / MIN_FPS;

    #define MAX_FPS 150
    #define MIN_FPS 30
    #define UPDATE_INTERVAL (1.0 / MAX_FPS * 1000)
    #define MAX_UPDATES (MAX_FPS / MIN_FPS)

    const int SKIP_TICKS = 100000/60;
    int screen_delay = 3.5;

    int ticks = 0;
    int delay;
    int balls;

    Uint32 start;

    //Start the update timer
    update.start();

    //Start the frame timer
    fps.start();
    double currentTime;

    std::cout << "Gra \"Arkanoid\" - ver. 0.51 zostala uruchomiona.\n";


    /* START OF MAIN LOOP */
    while ( !done )
    {
        //if (lastFrameTime == 0.0)
        //{
           // lastFrameTime = SDL_GetTicks();
        //}

        //static double lastFrameTime = 0.0;
        //static double cyclesLeftOver = 0.0;
        //double currentTime;
        //double updateIterations;


        currentTime = SDL_GetTicks();


        //_cprintf(sprintf(currentTime));
        //updateIterations = ((currentTime - lastFrameTime) + cyclesLeftOver);


        //if (updateIterations > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL))
        //{
        //    updateIterations = (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL);
        //}

        /*
        while (updateIterations > UPDATE_INTERVAL)
        {
            updateIterations -= UPDATE_INTERVAL;
            update_game->updateGame(); // Update game state a variable number of times
        }

        cyclesLeftOver = updateIterations;
        lastFrameTime = currentTime;
        */

        //start = SDL_GetTicks();



        //// updating actual frame ////
        update_game->updateGame();

        //if( 1000/MAX_FPS>SDL_GetTicks()-start )
        //    SDL_Delay( 1000/MAX_FPS - (SDL_GetTicks() - start) );

        //ticks = fps.get_ticks();
        //std::fstream zapisz( "plik.txt", std::ios::out );
        //zapisz << ticks << std::endl;
        //zapisz.flush();
        //zapisz.close();


        //balls = update_game -> getBallNumbers();
        //if( ticks < SKIP_TICKS )
        //    SDL_Delay(SKIP_TICKS - ticks/*5*/);
        //else
        //{
        //    int cos = 2-balls+1;

        //    if( cos <= 0)
        //        cos = 1;

        //    SDL_Delay(cos);
        //}



        //SDL_Delay(balls);

        SDL_RenderClear(sdl_renderer);
        renderer->Render();

        if ( update_game->done == true )
            done = true;

        if ( update_game->slow_down == true )
            SDL_Delay(23);
        //else
        //    screen_delay = 3.5;

        //// update the screen ////
        //if( ticks > 0 )
        //    SDL_Delay(screen_delay);


        //// UPDATE SCREEN: ////
        SDL_UpdateTexture(sdl_texture, NULL, screen_surface->pixels, screen_surface->pitch);

        SDL_RenderCopy(sdl_renderer, sdl_texture, NULL, NULL);

        // Only without texture:
        //SDL_UpdateWindowSurface( window );

        SDL_RenderPresent(sdl_renderer);


        //SDL_Delay(balls);

        //balls = update_game -> getBallNumbers();

        //if( 1000/MAX_FPS>SDL_GetTicks()-currentTime )
        //    SDL_Delay( 1000/MAX_FPS - (SDL_GetTicks() - currentTime/**(balls*0.75))*/ ) );

        frame++;

        //if( fps.get_ticks() < SKIP_TICKS )
        //{
            //Sleep( SKIP_TICKS - GetTickCount() );
            //SDL_Delay( SKIP_TICKS - fps.get_ticks() );
            //SDL_Delay( 1 );
        //}

        //If a second has passed since the caption was last updated
        if( update.get_ticks() > 1000 )
        {
            //The frame rate as a string
            std::stringstream caption;

            //Calculate the frames per second and create the string
            caption << "Cosmonoid v. 0.57 - FPS: " << frame / ( fps.get_ticks() / 1000.f );

            //Reset the caption
            SDL_SetWindowTitle( window, caption.str().c_str() );

            //Restart the update timer
            update.start();
        }

    }
    /* end main loop */

    /* make sure SDL cleans up before exit */
    atexit( SDL_Quit );

    SDL_Quit();
    return 0;
}
