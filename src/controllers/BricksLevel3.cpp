#include "model/BricksLevel3.h"

std::map<const int, SDL_Rect*> BricksLevel3::destinations;
std::map<const int, SDL_Rect*> BricksLevel3::sources;

std::vector<int> BricksLevel3::bricksToDestroy;

BricksLevel3::BricksLevel3()
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

BricksLevel3::~BricksLevel3()
{
    SDL_FreeSurface(screen);

    delete screen;
}

/* Increment Brick ID, when new brick rectangles after creating are added to maps */
void BricksLevel3::incrementBrickID()
{
    brick_id += 1;
}

/* Group of methods to set positions of bricks and save them to maps */
void BricksLevel3::posAtStartBrownBricks()
{
    // brown block on screen
    // ########## First
    src_block_brown.x = 150;
    src_block_brown.y = 12;
    src_block_brown.w = 50;
    src_block_brown.h = 12;

    dst_block_brown.x = screen->w - 620;
    dst_block_brown.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown;

    sources[brick_id] = &src_block_brown;

    // ########## Second
    dst_block_brown2.x = screen->w - 620;
    dst_block_brown2.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown2;

    sources[brick_id] = &src_block_brown;

    // ########## Third
    dst_block_brown3.x = screen->w - 620;
    dst_block_brown3.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown3;

    sources[brick_id] = &src_block_brown;

    // ########## FOURTH
    dst_block_brown4.x = screen->w - 620;
    dst_block_brown4.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown4;

    sources[brick_id] = &src_block_brown;

    // ########## Fifth
    dst_block_brown5.x = screen->w - 620;
    dst_block_brown5.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown5;

    sources[brick_id] = &src_block_brown;

    // ########## Sixth
    dst_block_brown6.x = screen->w - 620;
    dst_block_brown6.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown6;

    sources[brick_id] = &src_block_brown;


    // ########## Seventh
    dst_block_brown7.x = screen->w - 320;
    dst_block_brown7.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown7;

    sources[brick_id] = &src_block_brown;

    // ########## Eight
    dst_block_brown8.x = screen->w - 320;
    dst_block_brown8.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown8;

    sources[brick_id] = &src_block_brown;

    // ########## Ninth
    dst_block_brown9.x = screen->w - 320;
    dst_block_brown9.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown9;

    sources[brick_id] = &src_block_brown;

    // ########## Ten
    dst_block_brown10.x = screen->w - 320;
    dst_block_brown10.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown10;

    sources[brick_id] = &src_block_brown;

    // ########## Eleven
    dst_block_brown11.x = screen->w - 320;
    dst_block_brown11.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown11;

    sources[brick_id] = &src_block_brown;

    // ########## Twelve
    dst_block_brown12.x = screen->w - 320;
    dst_block_brown12.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_brown12;

    sources[brick_id] = &src_block_brown;
}

void BricksLevel3::posAtStartGreenBricks()
{
    // green block on screen
    src_block_green.x = 0;
    src_block_green.y = 0;
    src_block_green.w = 50;
    src_block_green.h = 12;

    dst_block_green.x = screen->w - 570;
    dst_block_green.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green;

    sources[brick_id] = &src_block_green;

    // ########## Second
    dst_block_green2.x = screen->w - 570;
    dst_block_green2.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green2;

    sources[brick_id] = &src_block_green;

    // ########## Third
    dst_block_green3.x = screen->w - 570;
    dst_block_green3.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green3;

    sources[brick_id] = &src_block_green;

    // ########## FOURTH
    dst_block_green4.x = screen->w - 570;
    dst_block_green4.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green4;

    sources[brick_id] = &src_block_green;

    // ########## Fifth
    dst_block_green5.x = screen->w - 570;
    dst_block_green5.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green5;

    sources[brick_id] = &src_block_green;

    // ########## Sixth
    dst_block_green6.x = screen->w - 570;
    dst_block_green6.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green6;

    sources[brick_id] = &src_block_green;


    // ########## Seventh
    dst_block_green7.x = screen->w - 270;
    dst_block_green7.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green7;

    sources[brick_id] = &src_block_green;

    // ########## Eight
    dst_block_green8.x = screen->w - 270;
    dst_block_green8.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green8;

    sources[brick_id] = &src_block_green;

    // ########## Ninth
    dst_block_green9.x = screen->w - 270;
    dst_block_green9.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green9;

    sources[brick_id] = &src_block_green;

    // ########## Ten
    dst_block_green10.x = screen->w - 270;
    dst_block_green10.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green10;

    sources[brick_id] = &src_block_green;

    // ########## Eleven
    dst_block_green11.x = screen->w - 270;
    dst_block_green11.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green11;

    sources[brick_id] = &src_block_green;

    // ########## Twelve
    dst_block_green12.x = screen->w - 270;
    dst_block_green12.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_green12;

    sources[brick_id] = &src_block_green;
}

void BricksLevel3::posAtStartRedBricks()
{
    // red block on screen
    src_block_red.x = 75;
    src_block_red.y = 0;
    src_block_red.w = 50;
    src_block_red.h = 12;

    dst_block_red.x = screen->w - 520;
    dst_block_red.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red;

    sources[brick_id] = &src_block_red;

    // ########## Second
    dst_block_red2.x = screen->w - 520;
    dst_block_red2.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red2;

    sources[brick_id] = &src_block_red;

    // ########## Third
    dst_block_red3.x = screen->w - 520;
    dst_block_red3.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red3;

    sources[brick_id] = &src_block_red;

    // ########## FOURTH
    dst_block_red4.x = screen->w - 520;
    dst_block_red4.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red4;

    sources[brick_id] = &src_block_red;

    // ########## Fifth
    dst_block_red5.x = screen->w - 520;
    dst_block_red5.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red5;

    sources[brick_id] = &src_block_red;

    // ########## Sixth
    dst_block_red6.x = screen->w - 520;
    dst_block_red6.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red6;

    sources[brick_id] = &src_block_red;


    // ########## Seventh
    dst_block_red7.x = screen->w - 220;
    dst_block_red7.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red7;

    sources[brick_id] = &src_block_red;

    // ########## Eight
    dst_block_red8.x = screen->w - 220;
    dst_block_red8.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red8;

    sources[brick_id] = &src_block_red;

    // ########## Ninth
    dst_block_red9.x = screen->w - 220;
    dst_block_red9.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red9;

    sources[brick_id] = &src_block_red;

    // ########## Ten
    dst_block_red10.x = screen->w - 220;
    dst_block_red10.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red10;

    sources[brick_id] = &src_block_red;

    // ########## Eleven
    dst_block_red11.x = screen->w - 220;
    dst_block_red11.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red11;

    sources[brick_id] = &src_block_red;

    // ########## Twelve
    dst_block_red12.x = screen->w - 220;
    dst_block_red12.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_red12;

    sources[brick_id] = &src_block_red;
}

void BricksLevel3::posAtStartBlueBricks()
{
    // blue block on screen
    src_block_blue.x = 75;
    src_block_blue.y = 12;
    src_block_blue.w = 50;
    src_block_blue.h = 12;

    dst_block_blue.x = screen->w - 470;
    dst_block_blue.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue;

    sources[brick_id] = &src_block_blue;

    // ########## Second
    dst_block_blue2.x = screen->w - 470;
    dst_block_blue2.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue2;

    sources[brick_id] = &src_block_blue;

    // ########## Third
    dst_block_blue3.x = screen->w - 470;
    dst_block_blue3.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue3;

    sources[brick_id] = &src_block_blue;

    // ########## FOURTH
    dst_block_blue4.x = screen->w - 470;
    dst_block_blue4.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue4;

    sources[brick_id] = &src_block_blue;

    // ########## Fifth
    dst_block_blue5.x = screen->w - 470;
    dst_block_blue5.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue5;

    sources[brick_id] = &src_block_blue;

    // ########## Sixth
    dst_block_blue6.x = screen->w - 470;
    dst_block_blue6.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue6;

    sources[brick_id] = &src_block_blue;


    // ########## Seventh
    dst_block_blue7.x = screen->w - 170;
    dst_block_blue7.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue7;

    sources[brick_id] = &src_block_blue;

    // ########## Eight
    dst_block_blue8.x = screen->w - 170;
    dst_block_blue8.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue8;

    sources[brick_id] = &src_block_blue;

    // ########## Ninth
    dst_block_blue9.x = screen->w - 170;
    dst_block_blue9.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue9;

    sources[brick_id] = &src_block_blue;

    // ########## Ten
    dst_block_blue10.x = screen->w - 170;
    dst_block_blue10.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue10;

    sources[brick_id] = &src_block_blue;

    // ########## Eleven
    dst_block_blue11.x = screen->w - 170;
    dst_block_blue11.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue11;

    sources[brick_id] = &src_block_blue;

    // ########## Twelve
    dst_block_blue12.x = screen->w - 170;
    dst_block_blue12.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_blue12;

    sources[brick_id] = &src_block_blue;
}

void BricksLevel3::posAtStartVioletBricks()
{
    // violet block on screen
    src_block_violet.x = 0;
    src_block_violet.y = 12;
    src_block_violet.w = 50;
    src_block_violet.h = 12;

    dst_block_violet.x = screen->w - 420;
    dst_block_violet.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet;

    sources[brick_id] = &src_block_violet;

    // ########## Second
    dst_block_violet2.x = screen->w - 420;
    dst_block_violet2.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet2;

    sources[brick_id] = &src_block_violet;

    // ########## Third
    dst_block_violet3.x = screen->w - 420;
    dst_block_violet3.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet3;

    sources[brick_id] = &src_block_violet;

    // ########## FOURTH
    dst_block_violet4.x = screen->w - 420;
    dst_block_violet4.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet4;

    sources[brick_id] = &src_block_violet;

    // ########## Fifth
    dst_block_violet5.x = screen->w - 420;
    dst_block_violet5.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet5;

    sources[brick_id] = &src_block_violet;

    // ########## Sixth
    dst_block_violet6.x = screen->w - 420;
    dst_block_violet6.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet6;

    sources[brick_id] = &src_block_violet;


    // ########## Seventh
    dst_block_violet7.x = screen->w - 120;
    dst_block_violet7.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet7;

    sources[brick_id] = &src_block_violet;

    // ########## Eight
    dst_block_violet8.x = screen->w - 120;
    dst_block_violet8.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet8;

    sources[brick_id] = &src_block_violet;

    // ########## Ninth
    dst_block_violet9.x = screen->w - 120;
    dst_block_violet9.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet9;

    sources[brick_id] = &src_block_violet;

    // ########## Ten
    dst_block_violet10.x = screen->w - 120;
    dst_block_violet10.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet10;

    sources[brick_id] = &src_block_violet;

    // ########## Eleven
    dst_block_violet11.x = screen->w - 120;
    dst_block_violet11.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet11;

    sources[brick_id] = &src_block_violet;

    // ########## Twelve
    dst_block_violet12.x = screen->w - 120;
    dst_block_violet12.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_violet12;

    sources[brick_id] = &src_block_violet;
}

void BricksLevel3::posAtStartDarkBricks()
{
    // dark block on screen
    src_block_dark.x = 150;
    src_block_dark.y = 0;
    src_block_dark.w = 50;
    src_block_dark.h = 12;

    dst_block_dark.x = screen->w - 370;
    dst_block_dark.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark;

    sources[brick_id] = &src_block_dark;

    // ########## Second
    dst_block_dark2.x = screen->w - 370;
    dst_block_dark2.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark2;

    sources[brick_id] = &src_block_dark;

    // ########## Third
    dst_block_dark3.x = screen->w - 370;
    dst_block_dark3.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark3;

    sources[brick_id] = &src_block_dark;

    // ########## FOURTH
    dst_block_dark4.x = screen->w - 370;
    dst_block_dark4.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark4;

    sources[brick_id] = &src_block_dark;

    // ########## Fifth
    dst_block_dark5.x = screen->w - 370;
    dst_block_dark5.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark5;

    sources[brick_id] = &src_block_dark;

    // ########## Sixth
    dst_block_dark6.x = screen->w - 370;
    dst_block_dark6.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark6;

    sources[brick_id] = &src_block_dark;


    // ########## Seventh
    dst_block_dark7.x = screen->w - 70;
    dst_block_dark7.y = 300;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark7;

    sources[brick_id] = &src_block_dark;

    // ########## Eight
    dst_block_dark8.x = screen->w - 70;
    dst_block_dark8.y = 250;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark8;

    sources[brick_id] = &src_block_dark;

    // ########## Ninth
    dst_block_dark9.x = screen->w - 70;
    dst_block_dark9.y = 200;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark9;

    sources[brick_id] = &src_block_dark;

    // ########## Ten
    dst_block_dark10.x = screen->w - 70;
    dst_block_dark10.y = 150;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark10;

    sources[brick_id] = &src_block_dark;

    // ########## Eleven
    dst_block_dark11.x = screen->w - 70;
    dst_block_dark11.y = 100;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark11;

    sources[brick_id] = &src_block_dark;

    // ########## Twelve
    dst_block_dark12.x = screen->w - 70;
    dst_block_dark12.y = 50;

    incrementBrickID();
    destinations[brick_id] = &dst_block_dark12;

    sources[brick_id] = &src_block_dark;
}

/* Group of methods to return proper objects */
SDL_Rect* BricksLevel3::getOneBrick(int map_index)
{
    return destinations[map_index];;
}

std::map<const int, SDL_Rect*>& BricksLevel3::getAllBricks()
{
    return destinations;
}

std::map<const int, SDL_Rect*>& BricksLevel3::getSourceBricks()
{
    return sources;
}

std::vector<int>& BricksLevel3::getTableOfIgnoredBricks()
{
    return bricksToDestroy;
}

/* Adding parameter at the end of the vector with numbers of bricks to destroy (when collision occured!) */
void BricksLevel3::addToTableIgnoredBricks(int brick)
{
    bricksToDestroy.push_back(brick);
}

void BricksLevel3::destroyBrick(int brick)
{
    destinations[brick]->w = 0;
    destinations[brick]->h = 0;

    destinations[brick]->x = -10;
    destinations[brick]->y = -10;
}

void BricksLevel3::clearData()
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

void BricksLevel3::replaceAllBricks()
{
    posAtStartBrownBricks();
    posAtStartGreenBricks();
    posAtStartRedBricks();
    posAtStartBlueBricks();
    posAtStartVioletBricks();
    posAtStartDarkBricks();
}
