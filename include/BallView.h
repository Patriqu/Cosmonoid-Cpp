#ifndef BALLVIEW_H
#define BALLVIEW_H

#include <SDL.h>
#include "SDL_image.h"

#include "ResManager.h"

#include "Ball.h"

class BallView
{
public:
    BallView();
    virtual ~BallView();

    void placeBall(int nr);

private:
    SDL_Surface* screen;
    Ball* ball;
};

#endif // BALLVIEW_H
