#ifndef PADDLEVIEW_H
#define PADDLEVIEW_H

#include <cstdlib>
#include <SDL.h>
#include "SDL_image.h"

#include "controllers/ResManager.h"

#include "model/Paddle.h"

class PaddleView
{
public:
    PaddleView();
    virtual ~PaddleView();

    void placePaddle();

private:
    SDL_Surface* screen;
    Paddle* paddle;
};

#endif // PADDLEVIEW_H
