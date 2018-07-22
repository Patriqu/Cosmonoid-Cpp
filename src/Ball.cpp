#include "Ball.h"

/* static declars: */
std::vector<SDL_Rect> Ball:: dst_ball;
int Ball:: ball_numbers;

/* functions: */
Ball::Ball( /*std::map<std::string, int>& surfer*/ )
    //: surf_nbs( surfer )
    : screen ( SDL_GetWindowSurface(SDL_GetWindowFromID(1)) )
{
}

/*
Ball:: Ball()
{
}
*/

Ball:: ~Ball()
{
}

SDL_Rect& Ball:: getBall( int nr )
{
    return dst_ball[nr];
}

int Ball:: getBallPosition( int nr, std:: string t )
{
    if ( t == "x" )
        return dst_ball[nr].x;
    else if ( t == "y" )
        return dst_ball[nr].y;
    else if ( t == "w" )
        return dst_ball[nr].w;
    else if ( t == "h" )
        return dst_ball[nr].h;
}

int Ball:: getBallNumbers()
{
    return ball_numbers;
}

int Ball:: createBall()
{
    SDL_Rect s;
    dst_ball.push_back(s);
    posBallAtStart( ball_numbers );
    ball_numbers++;

    return ball_numbers-1;
}

void Ball:: deleteBall( int nr )
{
    dst_ball.erase(dst_ball.begin() + nr);
    ball_numbers--;
}

void Ball:: resetBall()
{
    dst_ball.clear();
    ball_numbers = 0;
}

void Ball:: clearBalls()
{
    dst_ball.clear();
}

void Ball:: posBallAtStart( int nr )
{
    dst_ball_default.x = ( /*surf_nbs["width"]*/ screen->w - ResManager:: getInstance().getImageWidth( "ball" ) )/ 2;
    dst_ball_default.y = /*surf_nbs["height"]*/ screen->h - 56;
    dst_ball_default.w = 21;
    dst_ball_default.h = 20;

    dst_ball[nr].x = dst_ball_default.x;
    dst_ball[nr].y = dst_ball_default.y;
    dst_ball[nr].w = dst_ball_default.w;
    dst_ball[nr].h = dst_ball_default.h;
}

void Ball:: setBallMotion( int nr, std:: string t, int v )
{
    if ( t == "x" )
        dst_ball[nr].x -= v;
    else if ( t == "y" )
        dst_ball[nr].y -= v;
}

void Ball:: setBallPosition( int nr, std:: string t, int p )
{
    if ( t == "x" )
        dst_ball[nr].x = p;
    else if ( t == "y" )
        dst_ball[nr].y = p;
}

void Ball:: correctBottleneck( int nr, int offset )
{
    dst_ball[nr].x += offset;
}
