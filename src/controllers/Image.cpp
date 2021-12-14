#include "controllers/Image.h"

SDL_Color Image::bgd_color = {255, 255, 255, 1};

SDL_Surface* Image::menu_img = NULL;
SDL_Surface* Image::selection_img = NULL;

SDL_Surface* Image::paddle_img = NULL;
SDL_Surface* Image::paddle_war_img = NULL;
SDL_Surface* Image::ball_img = NULL;
SDL_Surface* Image::bullet_img = NULL;
SDL_Surface* Image::blocks_img = NULL;

SDL_Surface* Image::gun_pack = NULL;
SDL_Surface* Image::slow_pack = NULL;
SDL_Surface* Image::dup_pack = NULL; //
SDL_Surface* Image::live_pack = NULL;

Image::Image()
{
}

Image::~Image()
{
}

SDL_Surface* Image::loadImage(std::string attr, /*const char**/ std::string res)
{
    if (attr == "ball")
    {
        if (ball_img == NULL)
            ball_img = IMG_Load("img/ball.png");

        return ball_img;
    }
    else if (attr == "paddle")
    {
        if (paddle_img == NULL)
            paddle_img = IMG_Load("img/paddle_cosmic1.png" /*"img/paddle.png"*/);

        return paddle_img;
    }
    else if (attr == "paddle_war")
    {
        if (paddle_war_img == NULL)
            paddle_war_img = IMG_Load("img/paddle_cosmic1_gun.png" /*"img/paddle_w_gun.png"*/);

        return paddle_war_img;
    }
    else if (attr == "bullet")
    {
        if (bullet_img == NULL)
            bullet_img = IMG_Load("img/bullet.png");

        return bullet_img;
    }
    else if (attr == "blocks")
    {
        if (blocks_img == NULL)
            blocks_img = IMG_Load("img/blocks_table.png");

        return blocks_img;
    }
    else if (attr == "menu")
    {
        if (menu_img == NULL)
        {
            std::string temp = "img/menu_bgd_";
            temp += res;
            temp += ".png";
            const char* ctemp = temp.c_str();

            //menu_img = IMG_Load( ctemp /*"img/menu_bgd" + res + ".png"*/ );

            menu_img = IMG_Load("img/menu_bgd_480.png");
        }

        return menu_img;
    }
    else if (attr == "selection")
    {
        if (selection_img == NULL)
            selection_img = IMG_Load("img/selection.png");

        return selection_img;
    }

        /* BONUSES: */
    else if (attr == "gun_pack")
    {
        if (gun_pack == NULL)
            gun_pack = IMG_Load("img/gun_pack.png");

        return gun_pack;
    }
    else if (attr == "slow_pack")
    {
        if (slow_pack == NULL)
            slow_pack = IMG_Load("img/slow_pack.png");

        return slow_pack;
    }
    else if (attr == "dup_pack")
    {
        if (dup_pack == NULL)
            dup_pack = IMG_Load("img/dup_pack.png");

        return dup_pack;
    }
    else if (attr == "live_pack")
    {
        if (live_pack == NULL)
            live_pack = IMG_Load("img/live_pack.png");

        return live_pack;
    }

    else
        return NULL;
}

SDL_Surface* Image::sendImage(std::string img)
{
    if (img == "ball")
        return ball_img;
    else if (img == "paddle")
        return paddle_img;
    else if (img == "paddle_war")
        return paddle_war_img;
    else if (img == "bullet")
        return bullet_img;
    else if (img == "blocks")
        return blocks_img;
    else if (img == "menu")
        return menu_img;
    else if (img == "selection")
        return selection_img;

        /* BONUSES: */
    else if (img == "gun_pack")
        return gun_pack;
    else if (img == "slow_pack")
        return slow_pack;
    else if (img == "dup_pack")
        return dup_pack;
    else if (img == "live_pack")
        return live_pack;

    else
        return NULL;
}

SDL_Color Image::getBgdColor()
{
    return bgd_color;
}

int Image::sendImageWidth(std::string attr)
{
    if (attr == "ball")
        return ball_img->w;
    else if (attr == "paddle")
        return paddle_img->w;
    else if (attr == "paddle_war")
        return paddle_war_img->w;
    else if (attr == "bullet")
        return bullet_img->w;
    else if (attr == "blocks")
        return blocks_img->w;

        /* BONUSES: */
    else if (attr == "gun_pack")
        return gun_pack->w;
    else if (attr == "slow_pack")
        return slow_pack->w;
    else if (attr == "dup_pack")
        return dup_pack->w;
    else if (attr == "live_pack")
        return live_pack->w;

    else
        return 0;
}

int Image::sendImageHeight(std::string attr)
{
    if (attr == "ball")
        return ball_img->h;
    else if (attr == "paddle")
        return paddle_img->h;
    else if (attr == "paddle_war")
        return paddle_war_img->h;
    else if (attr == "bullet")
        return bullet_img->h;
    else if (attr == "blocks")
        return blocks_img->h;

        /* BONUSES: */
    else if (attr == "gun_pack")
        return gun_pack->h;
    else if (attr == "slow_pack")
        return slow_pack->h;
    else if (attr == "dup_pack")
        return dup_pack->h;
    else if (attr == "live_pack")
        return live_pack->h;

    else
        return 0;
}
