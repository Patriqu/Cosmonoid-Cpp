#ifndef BONUSVIEW_H
#define BONUSVIEW_H

#include <SDL.h>
#include "SDL_image.h"

#include <string>

#include "ResManager.h"

#include "Bonus.h"

class BonusView
{
    public:
        BonusView();
        virtual ~BonusView();

        void renderBonus();

    private:
        std::ofstream saving;

        SDL_Surface* screen;

        Bonus* bonus;

        static std:: string bonus_pack;

        void checkBonus();
};

#endif // BONUSVIEW_H
