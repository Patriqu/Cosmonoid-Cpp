/**
@file main.cpp
*/

#include <cstdlib>
#include <map>
#include <iostream>

#include "tools/rapidxml.hpp"
#include "tools/rapidxml_utils.hpp"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "controllers/Timer.h"
#include "rules/GameState.h"
#include "UpdateGame.h"
#include "Renderer.h"

#include "Constants/Config.h"

int main(int argc, char* argv[])
{
    //// READ CONFIG DATA ////
    bool is_fullscreen;
    int width;
    int height;

    rapidxml::file<> xmlFile("config/config.xml");

    rapidxml::xml_document<> document;
    try
    {
        document.parse<0>(xmlFile.data());
    }
    catch (rapidxml::parse_error p)
    {
        p.what();
    }

    rapidxml::xml_node<>* root = document.first_node("arkanoid");

    root = root->first_node("config");
    root = root->first_node("display");
    root = root->first_node("fullscreen");

    // CHECK SCREEN MODE (FULLSCREEN OR WINDOW):
    std::string str_full(root->value());
    if (str_full == "true")
        is_fullscreen = true;
    else
        is_fullscreen = false;

    std::cout << "Fullscreen: " << root->value() << std::endl;

    // CHECK SCREEN WIDTH:
    root = root->next_sibling("width");

    std::string str(root->value());
    width = atoi(str.c_str());
    std::cout << "Width: " << width << std::endl;

    // CHECK SCREEN HEIGHT:
    root = root->next_sibling("height");

    std::string str_2(root->value());
    height = atoi(str_2.c_str());
    std::cout << "Height: " << height << std::endl << std::endl;

    document.clear();

    //// Define a vector of velocities of context screen for objects ////
    std::map<std::string, int> surf_nbs;
    surf_nbs["width"] = 640;
    surf_nbs["height"] = 480;

    //// initialization of SDL ////
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    //// Initialize screen ////
    auto title = "Cosmonoid - SDL2";
    SDL_Window* window;

    if (is_fullscreen)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI);
    }
    else {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    }

    if (!window) return -1;

    //// set icon at taskbar ////
    SDL_Surface* icon = IMG_Load("img/icon.png");
    SDL_SetWindowIcon(window, icon);

    SDL_Renderer* sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdl_renderer)
        return -1;

    if (is_fullscreen)
        SDL_RenderSetLogicalSize(sdl_renderer, width, height);

    SDL_Texture* sdl_texture = SDL_CreateTexture(sdl_renderer,
                                                 SDL_PIXELFORMAT_ARGB8888,
                                                 SDL_TEXTUREACCESS_STREAMING,
                                                 width, height);

    SDL_Surface* screen_surface = SDL_GetWindowSurface(window);

    SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format, 255, 255, 255));

    //// Initialise TTF ////
    if (TTF_Init() == -1) { return -1; }

    // open 44.1KHz, signed 16bit, system byte order, stereo audio, using 1024 byte chunks
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(2);
    }

    /* **************** program main loop *************** */

    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    const int INIT_LEVEL = 1;

    GameState game_state;

    //// Main components
    auto* update_game = new UpdateGame(&game_state, keystate, INIT_LEVEL);
    auto* renderer = new Renderer(INIT_LEVEL, &game_state);

    int frameCount = 0;
    Timer fpsTimer;
    Timer captionUpdateTimer;

    #define MAX_FPS 150
    #define MIN_FPS 30
    #define UPDATE_INTERVAL (1.0 / MAX_FPS * 1000)
    #define MAX_UPDATES (MAX_FPS / MIN_FPS)

    captionUpdateTimer.start();
    fpsTimer.start();

    std::cout << title << " game launched\n";

    while (true)
    {
        SDL_GetTicks();

        update_game->updateGame();

        SDL_RenderClear(sdl_renderer);
        renderer->Render();

        if (update_game->done)
            break;

        if (UpdateGame::slow_down)
            SDL_Delay(23);

        //// UPDATE SCREEN: ////
        SDL_UpdateTexture(sdl_texture, nullptr, screen_surface->pixels, screen_surface->pitch);
        SDL_RenderCopy(sdl_renderer, sdl_texture, nullptr, nullptr);
        SDL_RenderPresent(sdl_renderer);

        frameCount++;

        //If a second has passed since the caption was last updated
        if (captionUpdateTimer.get_ticks() > 1000)
        {
            std::stringstream caption;
            caption << title << " - FPS: " << frameCount / (fpsTimer.get_ticks() / 1000);

            SDL_SetWindowTitle(window, caption.str().c_str());

            //captionUpdateTimer.start();
        }
    }

    atexit(SDL_Quit);
    SDL_Quit();
    return 0;
}
