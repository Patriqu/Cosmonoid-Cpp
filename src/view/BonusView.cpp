#include "view/BonusView.h"

std::string BonusView::bonus_pack = "none";

BonusView::BonusView()
    : screen(SDL_GetWindowSurface(SDL_GetWindowFromID(1))),
      bonus(new Bonus())
{
}

BonusView::~BonusView()
{
}

void BonusView::checkBonus()
{
    std::string bonus_name = bonus->getBonus();

    if (bonus_name == "gun")
    {
        bonus_pack = "gun_pack";
    }
    else if (bonus_name == "dup")
    {
        bonus_pack = "dup_pack";
    }
    else if (bonus_name == "slow")
    {
        bonus_pack = "slow_pack";
    }
    else if (bonus_name == "live")
    {
        bonus_pack = "live_pack";
    }
    else if (bonus_name == "none")
    {
        bonus_pack = "none";
    }
}

void BonusView::renderBonus()
{
    // Check if bonus is currently active
    checkBonus();

    // If it is then display pack with bonus at screen
    if (bonus_pack != "none")
    {
        SDL_Rect dst_bonus = bonus->getBonusPosition();

        dst_bonus.w = 25;
        dst_bonus.h = 25;

        // Blit image of bonus pack at screen
        SDL_BlitSurface(ResManager::getInstance().getImage(bonus_pack), 0, screen, &dst_bonus);
    }
}
