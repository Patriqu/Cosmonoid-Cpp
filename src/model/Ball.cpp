#include "model/Ball.h"

/* static declars: */
std::vector<SDL_Rect> Ball::dst_ball;
int Ball::ball_numbers;

/* functions: */
Ball::Ball()
    : screen(SDL_GetWindowSurface(SDL_GetWindowFromID(1)))
{
}

Ball::~Ball()
{
}

SDL_Rect& Ball::getBall(const int nr)
{
    return dst_ball[nr];
}

int Ball::getBallPosition(const int nr, const std::string t)
{
    if (t == "x")
        return dst_ball[nr].x;
    if (t == "y")
        return dst_ball[nr].y;
    if (t == "w")
        return dst_ball[nr].w;
    if (t == "h")
        return dst_ball[nr].h;

    return dst_ball[nr].x;
}

int Ball::getBallNumbers()
{
    return ball_numbers;
}

int Ball::createBall()
{
    SDL_Rect s;
    dst_ball.push_back(s);
    positionBallAtStart(ball_numbers);
    ball_numbers++;

    return ball_numbers - 1;
}

void Ball::deleteBall(const int nr)
{
    dst_ball.erase(dst_ball.begin() + nr);
    ball_numbers--;
}

void Ball::resetBalls()
{
    dst_ball.clear();
    ball_numbers = 0;
}

void Ball::clearBalls()
{
    dst_ball.clear();
}

void Ball::positionBallAtStart(const int nr)
{
    dst_ball_default.x = (screen->w - ResManager::getInstance().getImageWidth("ball")) / 2;
    dst_ball_default.y = screen->h - 56;
    dst_ball_default.w = 21;
    dst_ball_default.h = 20;

    dst_ball[nr].x = dst_ball_default.x;
    dst_ball[nr].y = dst_ball_default.y;
    dst_ball[nr].w = dst_ball_default.w;
    dst_ball[nr].h = dst_ball_default.h;
}

void Ball::setBallMotion(const int nr, const std::string t, const int v)
{
    if (t == "x")
        dst_ball[nr].x -= v;
    else if (t == "y")
        dst_ball[nr].y -= v;
}

void Ball::setBallPosition(const int nr, const std::string t, const int p)
{
    if (t == "x")
        dst_ball[nr].x = p;
    else if (t == "y")
        dst_ball[nr].y = p;
}

void Ball::correctBottleneck(const int nr, const int offset)
{
    dst_ball[nr].x += offset;
}
