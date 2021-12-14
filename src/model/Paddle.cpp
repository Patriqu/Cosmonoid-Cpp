#include "model/Paddle.h"

/* static declars: */
SDL_Rect Paddle::dst_paddle;
SDL_Rect Paddle::dst_bullet;
std::string Paddle::paddle_name = "paddle";

std::vector<SDL_Rect*> Paddle::dst_bullets;

bool Paddle::bullet_created = false;
bool Paddle::bullet_destroyed = false;

/* functions: */
Paddle::Paddle()
    : screen(SDL_GetWindowSurface(SDL_GetWindowFromID(1)))
{
}

Paddle::~Paddle()
{
}

SDL_Rect& Paddle::getPaddle()
{
    return dst_paddle;
}

int Paddle::getPaddlePosition(const std::string t)
{
    if (t == "x")
        return dst_paddle.x;
    if (t == "y")
        return dst_paddle.y;
    if (t == "w")
        return dst_paddle.w;
    if (t == "h")
        return dst_paddle.h;

    return dst_paddle.x;
}

std::string Paddle::getPaddleName()
{
    return this->paddle_name;
}

SDL_Rect& Paddle::getBullet()
{
    return dst_bullet;
}

bool Paddle::isBulletCreated()
{
    return bullet_created;
}

void Paddle::positionPaddleAtStart()
{
    /* Paddle destination at start the level */
    dst_paddle.x = (screen->w - ResManager::getInstance().getImageWidth("paddle")) / 2;
    dst_paddle.y = screen->h - 35;
    dst_paddle.w = ResManager::getInstance().getImageWidth("paddle"); //160;
    dst_paddle.h = ResManager::getInstance().getImageHeight("paddle"); //29;

    dst_paddle_default.x = dst_paddle.x;
    dst_paddle_default.y = dst_paddle.y;
}

void Paddle::setPaddleMotion(float v)
{
    dst_paddle.x += v;
}

void Paddle::setPaddlePosition(int v)
{
    dst_paddle.x = v;
}

void Paddle::changePaddle(std::string type)
{
    paddle_name = type;
}

void Paddle::createBullet()
{
    SDL_Rect dst_bullet;
    dst_bullet.x = dst_paddle.x + dst_paddle.w / 2;
    dst_bullet.y = dst_paddle.y - dst_paddle.h - 38;

    dst_bullets.push_back(&dst_bullet);

    bullet_created = true;
}

void Paddle::moveBullet()
{
    dst_bullet.y = dst_bullet.y - 4;
    std::cout << "dst_bullet.y: " << dst_bullet.y << std::endl;
}

void Paddle::destroyBullet()
{
    dst_bullet.x = 0;
    dst_bullet.y = 0;

    bullet_created = false;
    bullet_destroyed = true;
}
