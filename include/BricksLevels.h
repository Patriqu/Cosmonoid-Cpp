#ifndef BRICKSLEVELS_H
#define BRICKSLEVELS_H

#include <map>
#include <vector>

#include <SDL.h>
#include "SDL_image.h"

class BricksLevels
{
    public:
        virtual SDL_Rect* getOneBrick( int map_index ) = 0;
        virtual std:: map <const int, SDL_Rect* >& getAllBricks() = 0;
        virtual std:: map <const int, SDL_Rect* >& getSourceBricks() = 0;
        virtual std:: vector<int>& getTableOfIgnoredBricks() = 0;

        virtual void addToTableIgnoredBricks( int brick ) = 0;
        virtual void destroyBrick( int brick ) = 0;

        virtual void clearData() = 0;
        virtual void replaceAllBricks() = 0;
};

#endif // BRICKSLEVELS_H
