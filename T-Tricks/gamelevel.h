#include <math.h>

class GameLevel
{
public:
	GameLevel();
	void next();
	void update(int linesCleared);
	int getLevelNumber();
	int getTickTime();
	int getScore(int lines);
private:
	int levelNumber;
	int tickTime;

};
