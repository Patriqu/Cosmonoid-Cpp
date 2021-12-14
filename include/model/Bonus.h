#ifndef BONUS_H
#define BONUS_H

#include <SDL.h>
#include "SDL_image.h"

#include <string>
#include <cstdlib>  // for random digits
#include <ctime>    // for random digits

#include <iostream>
#include <ios>
#include <fstream>

#include "controllers/ResManager.h"

class Bonus
{
public:
    Bonus();
    virtual ~Bonus();

    void initiateGenerator();
    void randomBonus();

    void setBonusPosition(SDL_Rect bonus);

    void moveBonus();
    int executeBonus();

    void removeBonus();

    std::string getBonus();
    SDL_Rect& getBonusPosition();
    void clearBonus();

    static SDL_Rect dst_bonus;
    static bool bonus_set;

private:
    std::ofstream saving;
    static std::string actual_bonus;

    static int draw_number;

    void setBonus(std::string bonus_name);
};

#endif // BONUS_H
