#include "Bonus.h"

std::string Bonus::actual_bonus = "none";
int Bonus::draw_number = 0;
SDL_Rect Bonus::dst_bonus;
bool Bonus::bonus_set = false;

Bonus::Bonus()
{
}

Bonus::~Bonus()
{
}

void Bonus::initiateGenerator()
{
    // initiate generator of pseudonumbers:
    srand(time(nullptr));
}

/* Randomize occurence of bonus */
void Bonus::randomBonus()
{
    // Random number
    draw_number = rand() % 40 + 1;

    // choose bonus
    if (draw_number > 5 && draw_number < 10)
    {
        // Bonus: get gun
        setBonus("gun");
    }
    else if (draw_number > 35 && draw_number < 38)
    {
        // Bonus: new live
        setBonus("live");
    }
    else if (draw_number > 19 && draw_number < 27)
    {
        // Bonus: duplicate of ball
        setBonus("dup");
    }
    else if (draw_number > 10 && draw_number < 14)
    {
        // Bonus: slowing a ball
        setBonus("slow");
    }

    else
    {
        if (bonus_set == false)
            setBonus("none");
    }
}

/* After occurence a bonus - set it */
void Bonus::setBonus(std::string bonus_name)
{
    actual_bonus = bonus_name;
}

/* Return bonus */
std::string Bonus::getBonus()
{
    return actual_bonus;
}

SDL_Rect& Bonus::getBonusPosition()
{
    return dst_bonus;
}

void Bonus::clearBonus()
{
    actual_bonus = "none";
    bonus_set = false;
}

void Bonus::setBonusPosition(SDL_Rect bonus)
{
    dst_bonus.x = bonus.x;
    dst_bonus.y = bonus.y + bonus.h + 2;
}

void Bonus::moveBonus()
{
    if (actual_bonus != "none")
        dst_bonus.y += 2;
}

void Bonus::removeBonus()
{
    dst_bonus.x = 0;
    dst_bonus.y = 0;

    dst_bonus.w = 0;
    dst_bonus.y = 0;

    actual_bonus = "none";
    bonus_set = false;
}

int Bonus::executeBonus()
{
    if (actual_bonus == "gun")
    {
        removeBonus();

        return 1;
    }
    else if (actual_bonus == "live")
    {
        removeBonus();

        return 2;
    }

    else if (actual_bonus == "slow")
    {
        removeBonus();

        return 3;
    }
    else if (actual_bonus == "dup")
    {
        removeBonus();

        return 4;
    }
}
