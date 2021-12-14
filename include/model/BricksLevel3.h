#ifndef BRICKSLEVEL3_H
#define BRICKSLEVEL3_H

#include <string>
#include <map>
#include <vector>

#include <SDL.h>
#include "SDL_image.h"

#include "controllers/ResManager.h"

#include "controllers/BricksLevels.h"

class BricksLevel3 : public BricksLevels
{
public:
    BricksLevel3();
    virtual ~BricksLevel3();

    void incrementBrickID();

    SDL_Rect* getOneBrick(int map_index);
    std::map<const int, SDL_Rect*>& getAllBricks();
    std::map<const int, SDL_Rect*>& getSourceBricks();
    std::vector<int>& getTableOfIgnoredBricks();

    void addToTableIgnoredBricks(int brick);
    void destroyBrick(int brick);

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

    SDL_Rect dst_block_brown5;
    SDL_Rect dst_block_green5;
    SDL_Rect dst_block_red5;
    SDL_Rect dst_block_blue5;
    SDL_Rect dst_block_violet5;
    SDL_Rect dst_block_dark5;

    SDL_Rect dst_block_brown6;
    SDL_Rect dst_block_green6;
    SDL_Rect dst_block_red6;
    SDL_Rect dst_block_blue6;
    SDL_Rect dst_block_violet6;
    SDL_Rect dst_block_dark6;

    SDL_Rect dst_block_brown7;
    SDL_Rect dst_block_green7;
    SDL_Rect dst_block_red7;
    SDL_Rect dst_block_blue7;
    SDL_Rect dst_block_violet7;
    SDL_Rect dst_block_dark7;

    SDL_Rect dst_block_brown8;
    SDL_Rect dst_block_green8;
    SDL_Rect dst_block_red8;
    SDL_Rect dst_block_blue8;
    SDL_Rect dst_block_violet8;
    SDL_Rect dst_block_dark8;

    SDL_Rect dst_block_brown9;
    SDL_Rect dst_block_green9;
    SDL_Rect dst_block_red9;
    SDL_Rect dst_block_blue9;
    SDL_Rect dst_block_violet9;
    SDL_Rect dst_block_dark9;

    SDL_Rect dst_block_brown10;
    SDL_Rect dst_block_green10;
    SDL_Rect dst_block_red10;
    SDL_Rect dst_block_blue10;
    SDL_Rect dst_block_violet10;
    SDL_Rect dst_block_dark10;

    SDL_Rect dst_block_brown11;
    SDL_Rect dst_block_green11;
    SDL_Rect dst_block_red11;
    SDL_Rect dst_block_blue11;
    SDL_Rect dst_block_violet11;
    SDL_Rect dst_block_dark11;

    SDL_Rect dst_block_brown12;
    SDL_Rect dst_block_green12;
    SDL_Rect dst_block_red12;
    SDL_Rect dst_block_blue12;
    SDL_Rect dst_block_violet12;
    SDL_Rect dst_block_dark12;

    static std::map<const int, SDL_Rect*> destinations;
    static std::map<const int, SDL_Rect*> sources;

    static std::vector<int> bricksToDestroy;

    SDL_Rect temp_rect;
    SDL_Rect temp_src;

    int brick_id;
};

#endif // BRICKSLEVEL3_H
