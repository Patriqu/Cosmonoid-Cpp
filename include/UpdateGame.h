#ifndef UPDATEGAME_H
#define UPDATEGAME_H

#include <windows.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <Mmsystem.h>

#include <SDL.h>
#include "SDL_image.h"
//#include "SDL_mixer.h"

// Standard data modules of game:
#include "Gamestate.h"
#include "MainMenu.h"
#include "Collisions.h"
#include "GamePoints.h"
#include "Bonus.h"

#include "Paddle.h"
#include "Ball.h"

// Data about levels:
#include "BricksLevels.h"
#include "BricksLevel1.h"
#include "BricksLevel2.h"
#include "BricksLevel3.h"
#include "BricksLevel4.h"

#include "SoundSystem.h"

class UpdateGame
{
public:
    UpdateGame(GameState* game_state, const Uint8* key_state, int level);
    virtual ~UpdateGame();

    // Main method for Update the Game
    void updateGame();
    int getBallNumbers() const;

    bool done;
    static bool slow_down;
    static bool set_paddle_default_look;

private:
    void mainMenuHandle();

    // Methods for handle keyboard
    void keysHandle(const Uint8* keyState);
    void menuKeyHandle();
    void menuMouseHandle();
    void debugKeys(const Uint8* keyState);

    void setTimer();
    static void CALLBACK TimeProc(UINT uID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

    void bonusHandle();
    void activateBonusLaser();
    void activateBonusLive() const;
    void activateBonusSlowdown();
    void activateBonusDuplicateBall();

    // Game state change event handlers
    void onStartGame();
    void onResumeGame();
    void onNextLevel();
    void onLoseGame();
    void onWinGame();

    // Collision handling
    void wallCollisionHandle();
    void objectsCollisionHandle();

    // Change data about actual level (create new level object)
    void loadLevelAtStart();
    void removeBrick() const;
    void clearData();

    // Definitions of variables:
    GameState* game_state;
    SDL_Surface* screen;

    const int MAX_LEVEL;
    const Uint8* keystate;
    int level;
    std::string current_state;

    SDL_Event event;

    // Motion:
    bool is_ball_motion;
    int MOTION_RATE_BALL_Y;
    int MOTION_RATE_BALL_X;
    int MOTION_RATE_BALL_X_SLOW;
    int MOTION_RATE_BALL_Y_SLOW;
    int MOTION_RATE_PADDLE;
    std::vector<int> x_motion_rates;
    std::vector<int> y_motion_rates;

    // Defs of pointers to physical objects
    MainMenu* main_menu;

    Paddle* paddle;
    Ball* ball;
    BricksLevels* bricks_level;

    Collisions* collisions;
    GamePoints* game_points;
    Bonus* bonus;

    // Sounds
    std::unique_ptr<SoundSystem> sound_system;

    std::string detected_collision_brick;
    std::string detected_collision_paddle;
    std::string detected_collision_bonus;
    std::string detected_collision_shoot;

    int nr_of_collision;

    bool is_gun;
    bool is_shot;

    int actual_ball_count;
    int MAX_BALLS;

    static MMRESULT timer_id;

    bool start_menu_music;
};

#endif // UPDATEGAME_H
