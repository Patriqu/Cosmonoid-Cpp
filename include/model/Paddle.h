#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>
#include "SDL_image.h"

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include "controllers/ResManager.h"

class Paddle
{
public:
    Paddle();
    virtual ~Paddle();

    SDL_Rect& getPaddle();
    int getPaddlePosition(std::string t);
    std::string getPaddleName();
    SDL_Rect& getBullet();
    bool isBulletCreated();
    void positionPaddleAtStart();

    void setPaddleMotion(float v);
    void setPaddlePosition(int v);
    void changePaddle(std::string type);

    void createBullet();
    void moveBullet();
    void destroyBullet();

private:
    static SDL_Rect dst_paddle;
    static SDL_Rect dst_bullet;
    static std::vector<SDL_Rect*> dst_bullets;

    SDL_Rect dst_paddle_default;

    static std::string paddle_name;

    static bool bullet_created;
    static bool bullet_destroyed;

    SDL_Surface* screen;
};

#endif // PADDLE_H
