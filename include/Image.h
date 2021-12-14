#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include "SDL_image.h"

#include <string>
#include <fstream>

class Image
{
public:
    Image();
    virtual ~Image();

    static SDL_Surface* loadImage(std::string img, /*const char**/ std::string res);
    static void setBgdColor();

    static SDL_Surface* sendImage(std::string img);

    static SDL_Color getBgdColor();

    static int sendImageWidth(std::string attr);
    static int sendImageHeight(std::string attr);

private:
    static SDL_Color bgd_color;

    static SDL_Surface* menu_img;
    static SDL_Surface* selection_img;

    static SDL_Surface* paddle_img;
    static SDL_Surface* paddle_war_img;
    static SDL_Surface* bullet_img;
    static SDL_Surface* blocks_img;
    static SDL_Surface* ball_img;

    static SDL_Surface* gun_pack;
    static SDL_Surface* slow_pack;
    static SDL_Surface* dup_pack;
    static SDL_Surface* live_pack;
};

#endif // IMAGE_H
