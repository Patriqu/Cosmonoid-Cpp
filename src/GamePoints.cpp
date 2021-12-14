#include "GamePoints.h"

int GamePoints::scores = 0;
int GamePoints::lives = 3;
int GamePoints::level = 1;
bool GamePoints::changed_lives = false;
std::string GamePoints::end_state = "none";

GamePoints::GamePoints()
    : is_changed_color(false)
{
}

GamePoints::~GamePoints()
{
}

/* Methods to get objects */
int GamePoints::getScores()
{
    return scores;
}

int GamePoints::getLives()
{
    return lives;
}

std::string GamePoints::getEndState()
{
    return end_state;
}

int GamePoints::getLevelNumber()
{
    return level;
}

/* Methods to check and update objects and states */
bool GamePoints::isChangedLives()
{
    if (changed_lives == true)
    {
        changed_lives = false;
        return true;
    }
    else
        return false;
}

bool GamePoints::isChangedColor()
{
    return is_changed_color;
}

void GamePoints::updateScores(int add_value)
{
    scores += add_value;
}

void GamePoints::updateLives(int add_value)
{
    lives += add_value;
    changed_lives = true;
}

void GamePoints::updateLevel(int add_value)
{
    level += add_value;

    if (level == 5)
        level = 1;
}

void GamePoints::resetLevel()
{
    level = 1;
}

void GamePoints::endGame(std::string state)
{
    if (state == "win")
        end_state = "win";
    else if (state == "lose")
        end_state = "lose";
    else if (state == "next_level")
        end_state = "next_level";

    else if (state == "new_start")
        end_state = "new_start";
    else if (state == "none")
        end_state = "none";
    else
        end_state = "none";
}

void GamePoints::resetData()
{
    scores = 0;
    lives = 3;
    changed_lives = true;
}

void GamePoints::changeTextColor()
{
    is_changed_color = true;
}
