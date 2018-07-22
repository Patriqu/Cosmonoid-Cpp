#include "PaddleView.h"

/* functions: */
PaddleView:: PaddleView()
    : screen ( SDL_GetWindowSurface(SDL_GetWindowFromID(1)) ),
    paddle ( new Paddle() )
{
}

PaddleView:: ~PaddleView()
{
    SDL_FreeSurface ( screen );
    free ( paddle );

    delete screen;
    delete paddle;
}

void PaddleView:: placePaddle()
{
    SDL_Rect temp_paddle = paddle -> getPaddle();
    std::string paddle_name = paddle -> getPaddleName();

    bool is_bullet_created = paddle -> isBulletCreated();

    if ( paddle_name == "paddle_war" )
        temp_paddle.y = temp_paddle.y - 28;

    SDL_BlitSurface( ResManager::getInstance().getImage( paddle_name ), 0, screen, &temp_paddle );

    if ( is_bullet_created == true )
    {
        SDL_Rect temp_bullet = paddle -> getBullet();

        SDL_BlitSurface( ResManager::getInstance().getImage( "bullet" ), 0, screen, &temp_bullet );
    }
}
