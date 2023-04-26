#include "model/Paddle.h"

SDL_Rect Paddle::dst_paddle;
std::string Paddle::paddle_name = "paddle";

std::vector<SDL_Rect*> Paddle::dst_bullets;
std::vector<SDL_Rect*> Paddle::dst_bullets_to_destroy;

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

void Paddle::positionPaddleAtStart()
{
    dst_paddle.x = (screen->w - ResManager::getInstance().getImageWidth("paddle")) / 2;
    dst_paddle.y = screen->h - 35;
    dst_paddle.w = ResManager::getInstance().getImageWidth("paddle");
    dst_paddle.h = ResManager::getInstance().getImageHeight("paddle");

    dst_paddle_default.x = dst_paddle.x;
    dst_paddle_default.y = dst_paddle.y;
    dst_paddle_default.w = dst_paddle.w;
    dst_paddle_default.h = dst_paddle.h;
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
}

std::vector<SDL_Rect*>& Paddle::getBullets() {
    return dst_bullets;
}

void Paddle::moveBullets()
{
    for (auto& bullet : dst_bullets) {
        bullet->y = bullet->y - 4;
    }
}

void Paddle::destroyOffscreenBullets() {
    for (auto& bullet : dst_bullets) {
        if (bullet->y < 0) {
            destroyBullet(bullet);
        }
    }
}

void Paddle::destroyBullet(SDL_Rect *pRect)
{
    pRect->x = 0;
    pRect->y = 0;
}

void Paddle::addLaserToDestroyLater(SDL_Rect bullet_rect) {
    dst_bullets_to_destroy.push_back(&bullet_rect);
}

void Paddle::destroyBulletsFromDestroyList() {
    std::destroy(dst_bullets_to_destroy.begin(), dst_bullets_to_destroy.end());
}
