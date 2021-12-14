#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <iostream>
#include <math.h>
#include <string>
#include <map>

#include <SDL.h>
#include "SDL_image.h"
#include "SDL_mixer.h"

class Collisions
{
public:
    Collisions();
    virtual ~Collisions();

    enum coll_detects { NONE = 0, HORIZONTAL, VERTICAL };

    coll_detects coll_side;

    std::string detectCollision(SDL_Rect A, std::map<const int, SDL_Rect*>& B);
    std::string detectCollision(SDL_Rect A, SDL_Rect B);

    int getCollidedBrick();
    int bounceBall();

    bool isBottleneck();

    void clearData();

private:
    bool is_brick_collided;
    static int nr_brick_collided;

    std::string return_text;

    bool bottleneck;
};

#endif // COLLISIONS_H
