#include "BricksLevels.h"

BricksLevels::BricksLevels()
{
}

BricksLevels::~BricksLevels()
{
}

SDL_Rect* BricksLevels:: getOneBrick( int map_index )
{
}

std:: map < const int, SDL_Rect* >& BricksLevels:: getAllBricks()
{
}

std:: map <const int, SDL_Rect* >& BricksLevels:: getSourceBricks()
{
}

std:: vector<int>& BricksLevels:: getTableOfIgnoredBricks()
{
}

void BricksLevels:: addToTableIgnoredBricks( int brick )
{
}

void BricksLevels:: destroyBrick( int brick )
{
}

void BricksLevels:: clearData()
{
}

void BricksLevels:: replaceAllBricks()
{
}
