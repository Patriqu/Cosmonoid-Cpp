#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>
#include "SDL_rect.h"
#include "SDL_image.h"

#include <list>
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
    void positionPaddleAtStart();

    void setPaddleMotion(float v);
    void setPaddlePosition(int v);
    void changePaddle(std::string type);

    void createBullet();
    std::list<SDL_Rect *>& getBullets();
    void moveBullets();
    void destroyOffscreenBullets();

    void addLaserToDestroyLater(SDL_Rect& bullet_rect);

    void destroyBulletsFromDestroyList();

    bool isBulletsExists();

private:

    static SDL_Rect dst_paddle;
    static std::list<SDL_Rect*> dst_bullets;
    static std::list<SDL_Rect*> dst_bullets_to_destroy;
    SDL_Rect dst_paddle_default;

    static std::string paddle_name;

    SDL_Surface* screen;
};

#endif // PADDLE_H
