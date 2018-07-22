#ifndef BRICKSLEVEL2_H
#define BRICKSLEVEL2_H

#include <string>
#include <map>
#include <vector>

#include <SDL.h>
#include "SDL_image.h"

#include "ResManager.h"

#include "BricksLevels.h"

class BricksLevel2 : public BricksLevels
{
    public:
        BricksLevel2();
        virtual ~BricksLevel2();

        void incrementBrickID();

        SDL_Rect* getOneBrick( int map_index );
        std:: map < const int, SDL_Rect* >& getAllBricks();
        std:: map <const int, SDL_Rect* >& getSourceBricks();
        std:: vector<int>& getTableOfIgnoredBricks();

        void addToTableIgnoredBricks( int brick );
        void destroyBrick( int brick );

        void clearData();
        void replaceAllBricks();

    private:
        /* functions with start positions of colour bricks */
        void posAtStartBrownBricks();
        void posAtStartGreenBricks();
        void posAtStartRedBricks();
        void posAtStartBlueBricks();
        void posAtStartVioletBricks();
        void posAtStartDarkBricks();

        SDL_Surface* screen;

		SDL_Rect src_block_brown;
        SDL_Rect src_block_green;
        SDL_Rect src_block_red;
        SDL_Rect src_block_blue;
        SDL_Rect src_block_violet;
        SDL_Rect src_block_dark;

        SDL_Rect dst_block_brown;
        SDL_Rect dst_block_green;
        SDL_Rect dst_block_red;
        SDL_Rect dst_block_blue;
        SDL_Rect dst_block_violet;
        SDL_Rect dst_block_dark;

        SDL_Rect dst_block_brown2;
        SDL_Rect dst_block_green2;
        SDL_Rect dst_block_red2;
        SDL_Rect dst_block_blue2;
        SDL_Rect dst_block_violet2;
        SDL_Rect dst_block_dark2;

        SDL_Rect dst_block_brown3;
        SDL_Rect dst_block_green3;
        SDL_Rect dst_block_red3;
        SDL_Rect dst_block_blue3;
        SDL_Rect dst_block_violet3;
        SDL_Rect dst_block_dark3;

        SDL_Rect dst_block_brown4;
        SDL_Rect dst_block_green4;
        SDL_Rect dst_block_red4;
        SDL_Rect dst_block_blue4;
        SDL_Rect dst_block_violet4;
        SDL_Rect dst_block_dark4;

        static std:: map < const int, SDL_Rect* > destsMap;
        static std:: map < const int, SDL_Rect* > sourcesMap;

        static std:: vector<int> bricksToDestroy;

        SDL_Rect temp_rect;
        SDL_Rect temp_src;

        int brick_id;
};

#endif // BRICKSLEVEL2_H
