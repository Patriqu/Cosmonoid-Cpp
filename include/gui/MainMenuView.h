#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include <iostream>
#include <string>
#include <map>
#include <list>

#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "controllers/ResManager.h"

#include "MainMenu.h"

class MainMenuView
{
public:
    MainMenuView();
    virtual ~MainMenuView();

    void renderMenu();
    void initOptions();
    void updateDisplaySelection();
    void renderTexts();
    void updateTexts();

    std::string getScreenModeName();
    std::string getBgdName();

private:
    void changeToNextOption(std::string& text, char& c_text, const std::string value, const std::string language,
                            SDL_Surface* surface);

    std::string screen_mode_name;
    std::string resolution_name;
    std::string bgd_name;

    SDL_Surface* screen;
    MainMenu* main_menu;

    /* Font defs */
    TTF_Font* font;
    TTF_Font* font_sec;
    SDL_Color font_color;

    /* Surfaces */
    SDL_Surface* new_surface;
    SDL_Surface* trial_surface;
    SDL_Surface* options_surface;
    SDL_Surface* opt_screen_surface;
    SDL_Surface* opt_resolution_surface;
    SDL_Surface* opt_bgd_surface;
    SDL_Surface* opt_language_surface;
    SDL_Surface* opt_volume_sound_surface;
    SDL_Surface* opt_volume_music_surface;
    SDL_Surface* opt_back_surface;
    SDL_Surface* quit_surface;

    SDL_Surface* restart_warn_surface;

    /* Destinations rects */
    SDL_Rect bgd;
    SDL_Rect selection_dst;

    SDL_Rect new_dest;
    SDL_Rect trial_dest;
    SDL_Rect options_dest;
    SDL_Rect opt_screen_dest;
    SDL_Rect opt_resolution_dest;
    SDL_Rect opt_bgd_dest;
    SDL_Rect opt_language_dest;
    SDL_Rect opt_volume_sound_dest;
    SDL_Rect opt_volume_music_dest;
    SDL_Rect opt_back_dest;
    SDL_Rect quit_dest;

    SDL_Rect restart_warn_dest;

    /* Texts */
    std::list<std::string>::iterator screen_mode_iterator;
    std::list<std::string>::iterator resolution_iterator;
    std::list<std::string>::iterator background_iterator;
    std::list<std::string>::iterator language_iterator;
    std::list<std::string>::iterator volume_sound_iterator;
    std::list<std::string>::iterator volume_music_iterator;

    std::string text_new;
    std::string text_trial;
    std::string text_options;
    std::string text_opt_screen;
    std::string text_opt_resolution;
    std::string text_opt_bgd;
    std::string text_opt_language;
    std::string text_opt_volume_sound;
    std::string text_opt_volume_music;
    std::string text_opt_back;
    std::string text_quit;

    std::string text_restart_warn;

    char* c_text_new;
    char* c_text_trial;
    char* c_text_options;
    char* c_text_opt_screen;
    char* c_text_opt_resolution;
    char* c_text_opt_bgd;
    char* c_text_opt_language;
    char* c_text_opt_volume_sound;
    char* c_text_opt_volume_music;
    char* c_text_opt_back;
    char* c_text_quit;

    char* c_text_restart_warn;

    int page;
};

#endif // MAINMENUVIEW_H
