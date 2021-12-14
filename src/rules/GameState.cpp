#include "rules/GameState.h"

GameState::GameState()
    : current_state(MAIN_MENU),
      state_local(MAIN_MENU)
{
}

GameState::~GameState()
{
}

void GameState::changeGameState(std::string set_state)
{
    if (set_state == "RESUME_GAME")
        current_state = RESUME_GAME;
    else if (set_state == "START_GAME")
        current_state = START_GAME;
    else if (set_state == "NEXT_LEVEL")
        current_state = NEXT_LEVEL;
    else if (set_state == "LOSE_GAME")
        current_state = LOSE_GAME;
    else if (set_state == "WIN_GAME")
        current_state = WIN_GAME;
    else if (set_state == "MAIN_MENU")
        current_state = MAIN_MENU;
}

std::string GameState::getCurrentState()
{
    if (current_state == RESUME_GAME)
        return "RESUME_GAME";
    else if (current_state == START_GAME)
        return "START_GAME";
    else if (current_state == NEXT_LEVEL)
        return "NEXT_LEVEL";
    else if (current_state == LOSE_GAME)
        return "LOSE_GAME";
    else if (current_state == WIN_GAME)
        return "WIN_GAME";
    else if (current_state == MAIN_MENU)
        return "MAIN_MENU";
    else
        return "other";
}
