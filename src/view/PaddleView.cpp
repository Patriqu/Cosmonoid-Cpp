#include "view/PaddleView.h"
#include "SDL_rect.h"

PaddleView::PaddleView()
    : screen(SDL_GetWindowSurface(SDL_GetWindowFromID(1))),
      paddle(new Paddle())
{
}

PaddleView::~PaddleView()
{
    SDL_FreeSurface(screen);
    free(paddle);

    delete screen;
    delete paddle;
}

void PaddleView::renderPaddle()
{
    SDL_Rect temp_paddle = paddle->getPaddle();
    std::string paddle_name = paddle->getPaddleName();

    if (paddle_name == "paddle_war")
        temp_paddle.y = temp_paddle.y - 28;

    SDL_BlitSurface(ResManager::getInstance().getImage(paddle_name), nullptr, screen, &temp_paddle);

    std::vector<SDL_Rect *> bullets = paddle->getBullets();
    for (auto& bullet : bullets) {
        SDL_BlitSurface(ResManager::getInstance().getImage("bullet"), nullptr, screen, bullet);
    }
}
