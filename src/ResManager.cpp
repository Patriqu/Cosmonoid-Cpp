#include "ResManager.h"

ResManager:: ResManager()
    : menu_img( NULL ),

    ball_img( NULL ),
    paddle_img( NULL ),
    paddle_war_img( NULL ),
    bullet_img( NULL ),
    blocks_img( NULL ),

    gun_pack_img( NULL ),
    slow_pack_img( NULL ),
    dup_pack_img( NULL ),
    live_pack_img( NULL )
{
}

ResManager:: ~ResManager()
{
    if( menu_img == NULL )
        SDL_FreeSurface( menu_img );

    if( ball_img == NULL )
        SDL_FreeSurface( ball_img );

    if( paddle_img == NULL )
        SDL_FreeSurface( paddle_img );

    if( blocks_img == NULL )
        SDL_FreeSurface( blocks_img );

    if( bullet_img == NULL )
        SDL_FreeSurface( bullet_img );


    if( gun_pack_img == NULL )
        SDL_FreeSurface( gun_pack_img );

    if( slow_pack_img == NULL )
        SDL_FreeSurface( slow_pack_img );

    if( dup_pack_img == NULL )
        SDL_FreeSurface( dup_pack_img );

    if( live_pack_img == NULL )
        SDL_FreeSurface( live_pack_img );
}

SDL_Surface* ResManager:: loadImageMenu(std:: string res)
{
    menu_img = Image:: loadImage( "menu", res );

    return menu_img;
}

SDL_Surface* ResManager:: loadImageSelection()
{
    selection_img = Image:: loadImage( "selection", "" );

    return selection_img;
}

SDL_Surface* ResManager:: loadImageBall()
{
    ball_img = Image:: loadImage( "ball", "" );

    return ball_img;
}

SDL_Surface* ResManager:: loadImagePaddle()
{
    paddle_img = Image:: loadImage( "paddle", "" );

    return paddle_img;
}

SDL_Surface* ResManager:: loadImagePaddleWar()
{
    paddle_img = Image:: loadImage( "paddle_war", "" );

    return paddle_war_img;
}

SDL_Surface* ResManager:: loadImageBullet()
{
    bullet_img = Image:: loadImage( "bullet", "" );

    return bullet_img;
}

SDL_Surface* ResManager:: loadImageBlocks()
{
    blocks_img = Image:: loadImage( "blocks", "" );

    return blocks_img;
}

/* METHODS FOR LOAD BONUSES PACKS */

SDL_Surface* ResManager:: loadImageGunPack()
{
    gun_pack_img = Image:: loadImage( "gun_pack", "" );

    return gun_pack_img;
}

SDL_Surface* ResManager:: loadImageSlowPack()
{
    slow_pack_img = Image:: loadImage( "slow_pack", "" );

    return slow_pack_img;
}

SDL_Surface* ResManager:: loadImageDupPack()
{
    dup_pack_img = Image:: loadImage( "dup_pack", "" );

    return dup_pack_img;
}

SDL_Surface* ResManager:: loadImageLivePack()
{
    live_pack_img = Image:: loadImage( "live_pack", "" );

    return live_pack_img;
}

SDL_Surface* ResManager:: getImage ( std:: string img )
{
    if ( img == "ball" )
        return Image:: sendImage( "ball" );
    else if ( img == "paddle" )
        return Image:: sendImage( "paddle" );
    else if ( img == "paddle_war" )
        return Image:: sendImage( "paddle_war" );
    else if ( img == "bullet" )
        return Image:: sendImage( "bullet" );
    else if ( img == "blocks" )
        return Image:: sendImage( "blocks" );
    else if ( img == "menu" )
        return Image:: sendImage( "menu" );
    else if ( img == "selection" )
        return Image:: sendImage( "selection" );

    /* BONUSES: */
    else if ( img == "gun_pack" )
        return Image:: sendImage( "gun_pack" );
    else if ( img == "slow_pack" )
        return Image:: sendImage( "slow_pack" );
    else if ( img == "dup_pack" )
        return Image:: sendImage( "dup_pack" );
    else if ( img == "live_pack" )
        return Image:: sendImage( "live_pack" );

    else
        return NULL;
}

SDL_Color ResManager:: getBgdColor()
{
    SDL_Color color = Image:: getBgdColor();
    return color;
}

int ResManager:: getImageWidth( std:: string attr )
{
    if ( attr == "ball" )
        return Image:: sendImageWidth( "ball" );
    else if ( attr == "paddle" )
        return Image:: sendImageWidth( "paddle" );
    else if ( attr == "paddle_war" )
        return Image:: sendImageWidth( "paddle_war" );
    else if ( attr == "bullet" )
        return Image:: sendImageWidth( "bullet" );
    else if ( attr == "blocks" )
        return Image:: sendImageWidth( "blocks" );

    /* BONUSES: */
    else if ( attr == "gun_pack" )
        return Image:: sendImageWidth( "gun_pack" );
    else if ( attr == "slow_pack" )
        return Image:: sendImageWidth( "slow_pack" );
    else if ( attr == "dup_pack" )
        return Image:: sendImageWidth( "dup_pack" );
    else if ( attr == "live_pack" )
        return Image:: sendImageWidth( "live_pack" );

    else
        return 0;
}

int ResManager:: getImageHeight( std:: string attr )
{
    if ( attr == "ball" )
        return Image:: sendImageHeight( "ball" );
    else if ( attr == "paddle" )
        return Image:: sendImageHeight( "paddle" );
    else if ( attr == "paddle_war" )
        return Image:: sendImageHeight( "paddle_war" );
    else if ( attr == "bullet" )
        return Image:: sendImageHeight( "bullet" );
    else if ( attr == "blocks" )
        return Image:: sendImageHeight( "blocks" );

    /* BONUSES: */
    else if ( attr == "gun_pack" )
        return Image:: sendImageHeight( "gun_pack" );
    else if ( attr == "slow_pack" )
        return Image:: sendImageHeight( "slow_pack" );
    else if ( attr == "dup_pack" )
        return Image:: sendImageHeight( "dup_pack" );
    else if ( attr == "live_pack" )
        return Image:: sendImageHeight( "live_pack" );

    else
        return 0;
}
