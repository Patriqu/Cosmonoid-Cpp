#ifndef BRICKSVIEWLEVELS_H
#define BRICKSVIEWLEVELS_H


#include <SDL.h>
#include "SDL_image.h"

#include <map>
#include <vector>

#include "ResManager.h"

#include "BricksLevels.h"
#include "BricksLevel1.h"
#include "BricksLevel2.h"
#include "BricksLevel3.h"
#include "BricksLevel4.h"

class BricksViewLevels
{
public:
    BricksViewLevels(int level);
    virtual ~BricksViewLevels();

    void changeDisplayLevel(int level);
    void placeAllBricks();

private:
    SDL_Surface* screen;
    BricksLevels* bricks_level;

    bool is_valid_state;

    void getLevelData(int level);
};

#endif // BRICKSVIEWLEVELS_H
