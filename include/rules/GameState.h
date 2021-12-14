#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <cstring>

class GameState
{
public:
    GameState();
    virtual ~GameState();

    enum Gamestate
    {
        MAIN_MENU,
        START_GAME,
        RESUME_GAME,
        PAUSE_GAME,
        NEXT_LEVEL,
        LOSE_GAME,
        WIN_GAME
    };

    Gamestate current_state;

    void changeGameState(std::string set_state);

    std::string getCurrentState();

private:
    Gamestate state_local;
};

#endif // GAMESTATE_H
