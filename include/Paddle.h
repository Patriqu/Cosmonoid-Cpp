#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>
#include "SDL_image.h"

#include <string>
#include <iostream>
#include <map>

#include "ResManager.h"

class Paddle
{
    public:
        Paddle( /*std::map<std::string, int>& surfer*/ );
        //Paddle();
        virtual ~Paddle();

        SDL_Rect& getPaddle();
        int getPaddlePosition( std:: string t );
        std::string getPaddleName();
        SDL_Rect& getBullet();
        bool isBulletCreated();
        void posPaddleAtStart();

        void setPaddleMotion( float v );
        void setPaddlePosition ( int v );
        void changePaddle( std::string type );

        void createBullet();
        void shoot();

    private:
        static SDL_Rect dst_paddle;
        static SDL_Rect dst_bullet;

        SDL_Rect dst_paddle_default;

        static std::string paddle_name;
        static bool bullet_created;

        SDL_Surface* screen;
        //std::map<std::string, int> surf_nbs;
};

#endif // PADDLE_H
