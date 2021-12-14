#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "SDL_image.h"

#include <string>
#include <vector>
#include <map>

#include "controllers/ResManager.h"

class Ball
{
public:
    Ball();
    virtual ~Ball();

    SDL_Rect& getBall(int nr);
    int getBallPosition(int nr, std::string t);
    int getBallNumbers();
    int createBall();
    void deleteBall(int nr);
    void resetBalls();
    void clearBalls();
    void positionBallAtStart(int nr);

    void setBallMotion(int nr, std::string t, int v);
    void setBallPosition(int nr, std::string t, int p);
    void correctBottleneck(int nr, int paddle_pos);

private:
    static std::vector<SDL_Rect> dst_ball;
    static int ball_numbers;

    SDL_Rect dst_ball_default;

    SDL_Surface* screen;
};

#endif // BALL_H
