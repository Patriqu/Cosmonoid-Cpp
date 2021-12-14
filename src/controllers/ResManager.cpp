#include "controllers/ResManager.h"

ResManager::ResManager()
    : menu_img(nullptr),
      selection_img(nullptr),

      ball_img(nullptr),
      paddle_img(nullptr),
      paddle_war_img(nullptr),
      bullet_img(nullptr),
      blocks_img(nullptr),

      gun_pack_img(nullptr),
      slow_pack_img(nullptr),
      dup_pack_img(nullptr),
      live_pack_img(nullptr)
{
}

ResManager::~ResManager()
{
    if (menu_img == nullptr)
        SDL_FreeSurface(menu_img);
    if (ball_img == nullptr)
        SDL_FreeSurface(ball_img);
    if (paddle_img == nullptr)
        SDL_FreeSurface(paddle_img);
    if (blocks_img == nullptr)
        SDL_FreeSurface(blocks_img);
    if (bullet_img == nullptr)
        SDL_FreeSurface(bullet_img);
    if (gun_pack_img == nullptr)
        SDL_FreeSurface(gun_pack_img);
    if (slow_pack_img == nullptr)
        SDL_FreeSurface(slow_pack_img);
    if (dup_pack_img == nullptr)
        SDL_FreeSurface(dup_pack_img);
    if (live_pack_img == nullptr)
        SDL_FreeSurface(live_pack_img);
}

SDL_Surface* ResManager::loadImageMenu(std::string res)
{
    menu_img = Image::loadImage("menu", res);
    return menu_img;
}

SDL_Surface* ResManager::loadImageSelection()
{
    selection_img = Image::loadImage("selection", "");
    return selection_img;
}

SDL_Surface* ResManager::loadImageBall()
{
    ball_img = Image::loadImage("ball", "");
    return ball_img;
}

SDL_Surface* ResManager::loadImagePaddle()
{
    paddle_img = Image::loadImage("paddle", "");
    return paddle_img;
}

SDL_Surface* ResManager::loadImagePaddleWar()
{
    paddle_img = Image::loadImage("paddle_war", "");
    return paddle_war_img;
}

SDL_Surface* ResManager::loadImageBullet()
{
    bullet_img = Image::loadImage("bullet", "");
    return bullet_img;
}

SDL_Surface* ResManager::loadImageBlocks()
{
    blocks_img = Image::loadImage("blocks", "");
    return blocks_img;
}

/* METHODS FOR LOAD BONUSES PACKS */

SDL_Surface* ResManager::loadImageGunPack()
{
    gun_pack_img = Image::loadImage("gun_pack", "");
    return gun_pack_img;
}

SDL_Surface* ResManager::loadImageSlowPack()
{
    slow_pack_img = Image::loadImage("slow_pack", "");
    return slow_pack_img;
}

SDL_Surface* ResManager::loadImageDupPack()
{
    dup_pack_img = Image::loadImage("dup_pack", "");
    return dup_pack_img;
}

SDL_Surface* ResManager::loadImageLivePack()
{
    live_pack_img = Image::loadImage("live_pack", "");
    return live_pack_img;
}

SDL_Surface* ResManager::getImage(const std::string img)
{
    return Image::sendImage(img);
}

SDL_Color ResManager::getBgdColor()
{
    const SDL_Color color = Image::getBgdColor();
    return color;
}

int ResManager::getImageWidth(const std::string attr)
{
    return Image::sendImageWidth(attr);
}

int ResManager::getImageHeight(const std::string attr)
{
    return Image::sendImageHeight(attr);
}
