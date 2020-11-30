/**
@file main.cpp
*/

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <windows.h>
#include <ctime>
#include <map>

#include <iostream>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Timer.h"
#include "GameState.h"
#include "UpdateGame.h"
#include "Renderer.h"

using namespace rapidxml;

int main ( int argc, char** argv )
{
    //// READ CONFIG DATA ////
    bool is_fullscreen = false;
    int width;
    int height;

    rapidxml::file<> xmlFile("config/config.xml");

    xml_document <> document;
    try {
        document.parse < 0/*parse_validate_closing_tags*/ >( xmlFile.data() );
    } catch( parse_error p ) {
        p.what();
    }

    xml_node <> * root = document.first_node("arkanoid");

    root = root->first_node("config");
    root = root->first_node("display");
    root = root->first_node("fullscreen");

    // CHECK SCREEN MODE (FULLSCREEN OR WINDOW):
    std::string str_full(root->value());
    if ( str_full == "true" )
        is_fullscreen = true;
    else
        is_fullscreen = false;

    std::cout << "Fullscreen: " << root->value() << std::endl;

    // CHECK SCREEN WIDTH:
    root = root->next_sibling("width");

    std::string str(root->value());
    width = atoi( str.c_str() );
    std::cout << "Width: " << width << std::endl;

    // CHECK SCREEN HEIGHT:
    root = root->next_sibling("height");

    std::string str_2(root->value());
    height = atoi( str_2.c_str() );
    std::cout << "Height: " << height << std::endl << std::endl;

    document.clear();


    //// Define a vector of velocities of context screen for objects ////
    std::map<std::string, int> surf_nbs;
    surf_nbs["width"] = 640;
    surf_nbs["height"] = 480;

    //// initialization of SDL ////
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    //// create a new window ////
    SDL_Window* window = nullptr;
    SDL_Renderer* sdl_renderer = nullptr;

    //// Initialize screen ////
    auto title = "Cosmonoid - SDL2 v0.57";
    
    if ( is_fullscreen == true )
    {
        window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/ );
        if (!window) return -1;
    }
    else if ( is_fullscreen == false )
    {
        window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI );
        if (!window) return -1;
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

    SDL_FillRect( screen_surface, nullptr, SDL_MapRGB( screen_surface->format, 255, 255, 255 ) );

    //// Initialise TTF ////
    if ( TTF_Init() == -1 ) { return -1; }

    // open 44.1KHz, signed 16bit, system byte order,
    // stereo audio, using 1024 byte chunks
    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(2);
    }


    /* **************** program main loop *************** */

    //// Definitions of vars used in main loop ////
    const Uint8* keystate = SDL_GetKeyboardState( nullptr );

    const int INIT_LEVEL = 1;

    //// at start default state is "Begin game"
    GameState game_state;

    //// Defs program main components ////
    UpdateGame* update_game = new UpdateGame(&game_state, keystate, INIT_LEVEL);
    Renderer* renderer = new Renderer(INIT_LEVEL, &game_state);

    int frame = 0;                      //Keep track of the frame count
    Timer fpsTimer;
    Timer updateTimer;                  //Timer used to update the caption

    #define MAX_FPS 150
    #define MIN_FPS 30
    #define UPDATE_INTERVAL (1.0 / MAX_FPS * 1000)
    #define MAX_UPDATES (MAX_FPS / MIN_FPS)

    updateTimer.start();
    fpsTimer.start();

    std::cout << title << " game launched\n";

    /* START OF MAIN LOOP */
    while (true)
    {
        SDL_GetTicks();

        update_game->updateGame();

        SDL_RenderClear(sdl_renderer);
        renderer->Render();

        if ( update_game->done == true )
            break;

        if ( update_game->slow_down == true )
            SDL_Delay(23);

        //// UPDATE SCREEN: ////
        SDL_UpdateTexture(sdl_texture, nullptr, screen_surface->pixels, screen_surface->pitch);

        SDL_RenderCopy(sdl_renderer, sdl_texture, nullptr, nullptr);

        SDL_RenderPresent(sdl_renderer);

        frame++;

        //If a second has passed since the caption was last updated
        if ( updateTimer.get_ticks() > 1000 )
        {
            std::stringstream caption;
            caption << title << " - FPS: " << frame / ( fpsTimer.get_ticks() / 1000.f );

            SDL_SetWindowTitle( window, caption.str().c_str() );

            updateTimer.start();
        }

    }
    /* end main loop */

    atexit( SDL_Quit );

    SDL_Quit();
    return 0;
}
