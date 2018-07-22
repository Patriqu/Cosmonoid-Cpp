#ifndef GAMEPOINTSVIEW_H
#define GAMEPOINTSVIEW_H

#include <stdio.h>
#include <string>
#include <sstream>

#include <SDL.h>
#include "SDL_ttf.h"

#include "GamePoints.h"

class GamePointsView
{
    public:
        GamePointsView();
        virtual ~GamePointsView();

        void placeAllPoints();
        void updatePointsText();
        void updateLivesDisplay();
        void updateLevelDisplay();

    private:
        SDL_Surface* screen;

        GamePoints* game_points;

        SDL_Surface* scores_surface;
        SDL_Surface* lives_surface;
        SDL_Surface* level_surface;

        SDL_Surface* end_surface;
        SDL_Surface* end_surface_2;

        TTF_Font* font;
        TTF_Font* font_end;
        TTF_Font* font_end_2;

        SDL_Color font_color;

        SDL_Rect score_dest;
        SDL_Rect lives_dest;
        SDL_Rect level_dest;

        std:: string text_score;
        std:: string text_lives;
        std:: string text_level;

        char* c_text_score;
        char* c_text_lives;
        char* c_text_level;
};

#endif // GAMEPOINTSVIEW_H
