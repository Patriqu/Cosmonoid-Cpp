#ifndef RESMANAGER_H
#define RESMANAGER_H

//#include <SDL.h>
#include <SDL.h>
#include "SDL_image.h"

#include <string>

#include "Image.h"

// Resource Manager is an singleton for the global access to a single instance of it, where other modules have easier
// access to different kind of resources, like textures, sound and music files.
// To access the resources: ResManager::getInstance().method()
class ResManager
{
public:
    virtual ~ResManager();

    static ResManager getInstance()
    {
        static ResManager res_manager;
        return res_manager;
    }

    SDL_Surface* loadImageMenu(std::string res);
    SDL_Surface* loadImageSelection();

    SDL_Surface* loadImageBall();
    SDL_Surface* loadImagePaddle();
    SDL_Surface* loadImagePaddleWar();
    SDL_Surface* loadImageBullet();
    SDL_Surface* loadImageBlocks();

    // bonuses
    SDL_Surface* loadImageGunPack();
    SDL_Surface* loadImageSlowPack();
    SDL_Surface* loadImageDupPack();
    SDL_Surface* loadImageLivePack();
    
    SDL_Surface* getImage(std::string img);
    
    SDL_Color getBgdColor();
    
    int getImageWidth(std::string attr);
    int getImageHeight(std::string attr);

private:
    ResManager();

    // copy constructor
    ResManager(const ResManager&)
    {
    }

    ResManager& operator=(const ResManager&);

    SDL_Surface* menu_img;
    SDL_Surface* selection_img;

    SDL_Surface* ball_img;
    SDL_Surface* paddle_img;
    SDL_Surface* paddle_war_img;
    SDL_Surface* bullet_img;
    SDL_Surface* blocks_img;

    SDL_Surface* gun_pack_img;
    SDL_Surface* slow_pack_img;
    SDL_Surface* dup_pack_img;
    SDL_Surface* live_pack_img;
};

#endif // RESMANAGER_H
