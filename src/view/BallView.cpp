#include "view/BallView.h"

BallView::BallView()
    : screen(SDL_GetWindowSurface(SDL_GetWindowFromID(1))),
      ball(new Ball())
{
}

BallView::~BallView()
{
    SDL_FreeSurface(screen);
    // free ( ball );

    delete screen;
    delete ball;
}

void BallView::placeBall(int nr)
{
    for (int i = 0; i < ball->getBallNumbers(); i++)
    {
        SDL_Rect temp_ball = ball->getBall(i);
        SDL_BlitSurface(ResManager::getInstance().getImage("ball"), 0, screen, &temp_ball);
    }
}
