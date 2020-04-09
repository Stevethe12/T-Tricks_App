#include "gamelevel.h"

GameLevel::GameLevel()
{
	tickTime = 800;
	levelNumber = 0;
}

void GameLevel::update(int linesCleared)
{
	if (linesCleared / 10 > levelNumber)
	{
		next();
	}
}

void GameLevel::next()
{
	levelNumber += 1;
	tickTime = 1000 * (48.0 - (5.0*levelNumber)) / 60.0;
}

int GameLevel::getLevelNumber()
{
	return levelNumber;
}

int GameLevel::getTickTime()
{
	return tickTime;
}


int GameLevel::getScore(int lines)
{
	if (lines == 1)
	{
		return 40 * (levelNumber + 1);
	}
	else if (lines == 2)
	{
		return 100 * (levelNumber + 1);
	}
	else if (lines == 3)
	{
		return 300 * (levelNumber + 1);
	}
	else if (lines > 3)
	{
		return 300 * lines*(levelNumber + 1);
	}
	else
	{
		return 0;
	}
}