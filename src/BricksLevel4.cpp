#include "BricksLevel4.h"

std::map<const int, SDL_Rect*> BricksLevel4::destinations;
std::map<const int, SDL_Rect*> BricksLevel4::sources;

std::vector<int> BricksLevel4::bricksToDestroy;

BricksLevel4::BricksLevel4()
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

BricksLevel4::~BricksLevel4()
{
    SDL_FreeSurface(screen);

    delete screen;
}

/* Increment Brick ID, when new brick rectangles after creating are added to maps */
void BricksLevel4::incrementBrickID()
{
    brick_id += 1;
}

/* Group of methods to set positions of bricks and save them to maps */
void BricksLevel4::posAtStartBrownBricks()
{
    // brown block on screen
    src_block_brown.x = 150;
    src_block_brown.y = 12;
    src_block_brown.w = 50;
    src_block_brown.h = 12;

    dst_block_brown.x = screen->w - 610;
    dst_block_brown.y = 190;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown;

    sources[brick_id] = &src_block_brown;

    // ########## Second
    dst_block_brown2.x = screen->w - 540;
    dst_block_brown2.y = 40;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown2;

    sources[brick_id] = &src_block_brown;

    // ########## Third
    dst_block_brown3.x = screen->w - 290;
    dst_block_brown3.y = 145;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown3;

    sources[brick_id] = &src_block_brown;

    // ########## FOURTH
    dst_block_brown4.x = screen->w - 135;
    dst_block_brown4.y = 240;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown4;

    sources[brick_id] = &src_block_brown;
}

void BricksLevel4::posAtStartGreenBricks()
{
    // green block on screen
    src_block_green.x = 0;
    src_block_green.y = 0;
    src_block_green.w = 50;
    src_block_green.h = 12;

    dst_block_green.x = screen->w - 620;
    dst_block_green.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green;

    sources[brick_id] = &src_block_green;

    // ########## Second
    dst_block_green2.x = screen->w - 425;
    dst_block_green2.y = 325;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green2;

    sources[brick_id] = &src_block_green;

    // ########## Third
    dst_block_green3.x = screen->w - 470;
    dst_block_green3.y = 180;

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

void BricksLevel4::posAtStartRedBricks()
{
    // red block on screen
    src_block_red.x = 75;
    src_block_red.y = 0;
    src_block_red.w = 50;
    src_block_red.h = 12;

    dst_block_red.x = screen->w - 620;
    dst_block_red.y = 120;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red;

    sources[brick_id] = &src_block_red;

    // ########## Second
    dst_block_red2.x = screen->w - 150;
    dst_block_red2.y = 165;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red2;

    sources[brick_id] = &src_block_red;

    // ########## Third
    dst_block_red3.x = screen->w - 295;
    dst_block_red3.y = 265;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red3;

    sources[brick_id] = &src_block_red;

    // ########## FOURTH
    dst_block_red4.x = screen->w - 370;
    dst_block_red4.y = 260;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red4;

    sources[brick_id] = &src_block_red;
}

void BricksLevel4::posAtStartBlueBricks()
{
    // blue block on screen
    src_block_blue.x = 75;
    src_block_blue.y = 12;
    src_block_blue.w = 50;
    src_block_blue.h = 12;

    dst_block_blue.x = screen->w - 580;
    dst_block_blue.y = 260;

    //temp_rect = returnRect( dst_block_blue );
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
    dst_block_blue3.x = screen->w - 355;
    dst_block_blue3.y = 170;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue3;

    sources[brick_id] = &src_block_blue;

    // ########## FOURTH
    dst_block_blue4.x = screen->w - 250;
    dst_block_blue4.y = 210;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue4;

    sources[brick_id] = &src_block_blue;
}

void BricksLevel4::posAtStartVioletBricks()
{
    // violet block on screen
    src_block_violet.x = 0;
    src_block_violet.y = 12;
    src_block_violet.w = 50;
    src_block_violet.h = 12;

    dst_block_violet.x = screen->w - 460;
    dst_block_violet.y = 130;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet;

    sources[brick_id] = &src_block_violet;

    // ########## Second
    dst_block_violet2.x = screen->w - 335;
    dst_block_violet2.y = 340;

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
    dst_block_violet4.y = 330;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet4;

    sources[brick_id] = &src_block_violet;
}

void BricksLevel4::posAtStartDarkBricks()
{
    // dark block on screen
    src_block_dark.x = 150;
    src_block_dark.y = 0;
    src_block_dark.w = 50;
    src_block_dark.h = 12;

    dst_block_dark.x = screen->w - 520;
    dst_block_dark.y = 310;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark;

    sources[brick_id] = &src_block_dark;

    // ########## Second
    dst_block_dark2.x = screen->w - 430;
    dst_block_dark2.y = 240;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark2;

    sources[brick_id] = &src_block_dark;

    // ########## Third
    dst_block_dark3.x = screen->w - 180;
    dst_block_dark3.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark3;

    sources[brick_id] = &src_block_dark;

    // ########## FOURTH
    dst_block_dark4.x = screen->w - 270;
    dst_block_dark4.y = 60;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark4;

    sources[brick_id] = &src_block_dark;
}

/* Group of methods to return proper objects */
SDL_Rect* BricksLevel4::getOneBrick(int map_index)
{
    return destinations[map_index];
}

std::map<const int, SDL_Rect*>& BricksLevel4::getAllBricks()
{
    return destinations;
}

std::map<const int, SDL_Rect*>& BricksLevel4::getSourceBricks()
{
    return sources;
}

std::vector<int>& BricksLevel4::getTableOfIgnoredBricks()
{
    return bricksToDestroy;
}

/* Adding parameter at the end of the vector with numbers of bricks to destroy (when collision occured!) */
void BricksLevel4::addToTableIgnoredBricks(int brick)
{
    bricksToDestroy.push_back(brick);
}

void BricksLevel4::destroyBrick(int brick)
{
    destinations[brick]->w = 0;
    destinations[brick]->h = 0;

    destinations[brick]->x = -10;
    destinations[brick]->y = -10;
}

void BricksLevel4::clearData()
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

void BricksLevel4::replaceAllBricks()
{
    posAtStartBrownBricks();
    posAtStartGreenBricks();
    posAtStartRedBricks();
    posAtStartBlueBricks();
    posAtStartVioletBricks();
    posAtStartDarkBricks();
}
