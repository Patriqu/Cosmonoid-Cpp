#include "model/BricksLevel1.h"

std::map<const int, SDL_Rect*> BricksLevel1::destinations;
std::map<const int, SDL_Rect*> BricksLevel1::sources;

std::vector<int> BricksLevel1::bricksToDestroy;

BricksLevel1::BricksLevel1()
    : screen(SDL_GetWindowSurface(SDL_GetWindowFromID(1))),
      brick_id(0)
{
    /* call functions with start position of colour bricks */
    posAtStartBrownBricks();
    posAtStartGreenBricks();
    posAtStartRedBricks();
    posAtStartBlueBricks();
    posAtStartVioletBricks();
    posAtStartDarkBricks();
}

BricksLevel1::~BricksLevel1()
{
    SDL_FreeSurface(screen);

    delete screen;
}

/* Increment Brick ID, when new brick rectangles after creating are added to maps */
void BricksLevel1::incrementBrickID()
{
    brick_id += 1;
}

/* Group of methods to set positions of bricks and save them to maps */
void BricksLevel1::posAtStartBrownBricks()
{
    // brown block on screen
    src_block_brown.x = 150;
    src_block_brown.y = 12;
    src_block_brown.w = 50;
    src_block_brown.h = 12;

    dst_block_brown.x = screen->w - 600;
    dst_block_brown.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown;

    sources[brick_id] = &src_block_brown;

    // ########## Second
    dst_block_brown2.x = screen->w - 450;
    dst_block_brown2.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown2;

    sources[brick_id] = &src_block_brown;

    // ########## Third
    dst_block_brown3.x = screen->w - 100;
    dst_block_brown3.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown3;

    sources[brick_id] = &src_block_brown;

    // ########## FOURTH
    dst_block_brown4.x = screen->w - 300;
    dst_block_brown4.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown4;

    sources[brick_id] = &src_block_brown;
}

void BricksLevel1::posAtStartGreenBricks()
{
    // green block on screen
    src_block_green.x = 0;
    src_block_green.y = 0;
    src_block_green.w = 50;
    src_block_green.h = 12;

    dst_block_green.x = screen->w - 550;
    dst_block_green.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green;

    sources[brick_id] = &src_block_green;

    // ########## Second
    dst_block_green2.x = screen->w - 550;
    dst_block_green2.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green2;

    sources[brick_id] = &src_block_green;

    // ########## Third
    dst_block_green3.x = screen->w - 50;
    dst_block_green3.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green3;

    sources[brick_id] = &src_block_green;

    // ########## FOURTH
    dst_block_green4.x = screen->w - 350;
    dst_block_green4.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green4;

    sources[brick_id] = &src_block_green;
}

void BricksLevel1::posAtStartRedBricks()
{
    // red block on screen
    src_block_red.x = 75;
    src_block_red.y = 0;
    src_block_red.w = 50;
    src_block_red.h = 12;

    dst_block_red.x = screen->w - 500;
    dst_block_red.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red;

    sources[brick_id] = &src_block_red;

    // ########## Second
    dst_block_red2.x = screen->w - 500;
    dst_block_red2.y = 100;

    //temp_rect = returnRect( dst_block_red2 );
    incrementBrickID();
    destinations[brick_id] = &dst_block_red2;

    sources[brick_id] = &src_block_red;

    // ########## Third
    dst_block_red3.x = screen->w - 100;
    dst_block_red3.y = 100;

    //temp_rect = returnRect( dst_block_red2 );
    incrementBrickID();
    destinations[brick_id] = &dst_block_red3;

    sources[brick_id] = &src_block_red;

    // ########## FOURTH
    dst_block_red4.x = screen->w - 200;
    dst_block_red4.y = 50; // ( screen->h - 540 );

    //temp_rect = returnRect( dst_block_green2 );
    incrementBrickID();
    destinations[brick_id] = &dst_block_red4;

    sources[brick_id] = &src_block_red;
}

void BricksLevel1::posAtStartBlueBricks()
{
    // blue block on screen
    src_block_blue.x = 75;
    src_block_blue.y = 12;
    src_block_blue.w = 50;
    src_block_blue.h = 12;

    dst_block_blue.x = screen->w - 450;
    dst_block_blue.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue;

    sources[brick_id] = &src_block_blue;

    // ########## Second
    dst_block_blue2.x = screen->w - 400;
    dst_block_blue2.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue2;

    sources[brick_id] = &src_block_blue;

    // ########## Third
    dst_block_blue3.x = screen->w - 150;
    dst_block_blue3.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue3;

    sources[brick_id] = &src_block_blue;

    // ########## FOURTH
    dst_block_blue4.x = screen->w - 300;
    dst_block_blue4.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue4;

    sources[brick_id] = &src_block_blue;
}

void BricksLevel1::posAtStartVioletBricks()
{
    // violet block on screen
    src_block_violet.x = 0;
    src_block_violet.y = 12;
    src_block_violet.w = 50;
    src_block_violet.h = 12;

    dst_block_violet.x = screen->w - 400;
    dst_block_violet.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet;

    sources[brick_id] = &src_block_violet;

    // ########## Second
    dst_block_violet2.x = screen->w - 600;
    dst_block_violet2.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet2;

    sources[brick_id] = &src_block_violet;

    // ########## Third
    dst_block_violet3.x = screen->w - 200;
    dst_block_violet3.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet3;

    sources[brick_id] = &src_block_violet;

    // ########## FOURTH
    dst_block_violet4.x = screen->w - 250;
    dst_block_violet4.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet4;

    sources[brick_id] = &src_block_violet;
}

void BricksLevel1::posAtStartDarkBricks()
{
    // dark block on screen
    src_block_dark.x = 150;
    src_block_dark.y = 0;
    src_block_dark.w = 50;
    src_block_dark.h = 12;

    dst_block_dark.x = screen->w - 350;
    dst_block_dark.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark;

    sources[brick_id] = &src_block_dark;

    // ########## Second
    dst_block_dark2.x = screen->w - 50;
    dst_block_dark2.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark2;

    sources[brick_id] = &src_block_dark;

    // ########## Third
    dst_block_dark3.x = screen->w - 150;
    dst_block_dark3.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark3;

    sources[brick_id] = &src_block_dark;

    // ########## FOURTH
    dst_block_dark4.x = screen->w - 250;
    dst_block_dark4.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark4;

    sources[brick_id] = &src_block_dark;
}

/* Group of methods to return proper objects */
SDL_Rect* BricksLevel1::getOneBrick(int map_index)
{
    return destinations[map_index];
}

std::map<const int, SDL_Rect*>& BricksLevel1::getAllBricks()
{
    return destinations;
}

std::map<const int, SDL_Rect*>& BricksLevel1::getSourceBricks()
{
    return sources;
}

std::vector<int>& BricksLevel1::getTableOfIgnoredBricks()
{
    return bricksToDestroy;
}

/* Adding parameter at the end of the vector with numbers of bricks to destroy (when collision occured!) */
void BricksLevel1::addToTableIgnoredBricks(int brick)
{
    bricksToDestroy.push_back(brick);
}

void BricksLevel1::destroyBrick(int brick)
{
    destinations[brick]->w = 0;
    destinations[brick]->h = 0;

    destinations[brick]->x = -10;
    destinations[brick]->y = -10;
}

void BricksLevel1::clearData()
{
    for (int ignore_iter = bricksToDestroy.size() - 1; ignore_iter >= 0; --ignore_iter)
    {
        bricksToDestroy[ignore_iter] = 0;
        bricksToDestroy.pop_back();
    }

    bricksToDestroy.resize(0);

    std::map<const int, SDL_Rect*>::const_iterator src_iter;
    std::map<const int, SDL_Rect*>::const_iterator dst_iter;
    std::vector<int>::const_iterator ignore_iter;

    sources.erase(sources.begin(), sources.end());
    destinations.erase(destinations.begin(), destinations.end());

    brick_id = 0;
}

void BricksLevel1::replaceAllBricks()
{
    posAtStartBrownBricks();
    posAtStartGreenBricks();
    posAtStartRedBricks();
    posAtStartBlueBricks();
    posAtStartVioletBricks();
    posAtStartDarkBricks();
}
