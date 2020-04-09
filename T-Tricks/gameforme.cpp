#include "gameforme.h"
using namespace std;

GameForme::GameForme(int type)
{
	if (type == FORMEI)
	{
		matrice = new int*[MAX_SIZE];
		matrice[0] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[1] = new int[MAX_SIZE] {0, 0, 1, 0, 0};
		matrice[2] = new int[MAX_SIZE] {0, 0, 1, 0, 0};
		matrice[3] = new int[MAX_SIZE] {0, 0, 1, 0, 0};
		matrice[4] = new int[MAX_SIZE] {0, 0, 1, 0, 0};
	}
	else if (type == FORMEJ)
	{
		matrice = new int*[MAX_SIZE];
		matrice[0] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[1] = new int[MAX_SIZE] {0, 1, 0, 0, 0};
		matrice[2] = new int[MAX_SIZE] {0, 1, 1, 1, 0};
		matrice[3] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[4] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
	}
	else if (type == FORMEL)
	{
		matrice = new int*[MAX_SIZE];
		matrice[0] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[1] = new int[MAX_SIZE] {0, 0, 0, 1, 0};
		matrice[2] = new int[MAX_SIZE] {0, 1, 1, 1, 0};
		matrice[3] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[4] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
	}
	else if (type == FORMEO)
	{

		matrice = new int*[MAX_SIZE];
		matrice[0] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[1] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[2] = new int[MAX_SIZE] {0, 0, 1, 1, 0};
		matrice[3] = new int[MAX_SIZE] {0, 0, 1, 1, 0};
		matrice[4] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
	}
	else if (type == FORMES)
	{
		matrice = new int*[MAX_SIZE];
		matrice[0] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[1] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[2] = new int[MAX_SIZE] {0, 0, 1, 1, 0};
		matrice[3] = new int[MAX_SIZE] {0, 1, 1, 0, 0};
		matrice[4] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
	}
	else if (type == FORMET)
	{
		matrice = new int*[MAX_SIZE];
		matrice[0] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[1] = new int[MAX_SIZE] {0, 0, 1, 0, 0};
		matrice[2] = new int[MAX_SIZE] {0, 1, 1, 1, 0};
		matrice[3] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[4] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
	}
	else if (type == FORMEZ)
	{
		matrice = new int*[MAX_SIZE];
		matrice[0] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[1] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
		matrice[2] = new int[MAX_SIZE] {0, 1, 1, 0, 0};
		matrice[3] = new int[MAX_SIZE] {0, 0, 1, 1, 0};
		matrice[4] = new int[MAX_SIZE] {0, 0, 0, 0, 0};
	}
	typeForme = type;
	ispreview = false;
	x = 5;
	y = 2;
}

GameForme::~GameForme()
{
	delete[] matrice;
}

int GameForme::getX()
{
	return x;
}
int GameForme::getY()
{
	return y;
}
void GameForme::setX(int x1)
{
	x = x1;
}
void GameForme::setY(int y1)
{
	y = y1;
}

void GameForme::tourner()
{
	tourner(DROITE);
}

void GameForme::tourner(int direction)
{
	int **tmp = new int*[MAX_SIZE];

	for (int i = 0; i < MAX_SIZE; i++)
	{
		tmp[i] = new int[MAX_SIZE] {0};
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (direction == GAUCHE)
			{
				tmp[i][j] = matrice[j][i];
			}
			else
			{
				tmp[i][j] = matrice[MAX_SIZE - 1 - j][i];
			}
		}
	}


	delete matrice;
	matrice = tmp;
}


int GameForme::getTile(int i, int j)
{
	if (i >= MAX_SIZE || j >= MAX_SIZE || i < 0 || j < 0)
	{
		return 0;
	}
	return matrice[i][j];
}

int GameForme::getTileGlobal(int i, int j)
{
	int offsetX = -(x - j - 2);
	int offsetY = -(y - i - 2);
	if (offsetX > 0 && offsetX < MAX_SIZE && offsetY > 0 && offsetY < MAX_SIZE)
	{
		return matrice[offsetY][offsetX];
	}
	else
	{
		return 0;
	}
}
int GameForme::getType()
{
	return typeForme;
}

void GameForme::setPreview(bool val)
{
	ispreview = val;
}

bool GameForme::isPreview()
{
	return ispreview;
}

GameForme* GameForme::copy()
{
	GameForme *copy = new GameForme(typeForme);
	copy->setX(x);
	copy->setY(y);
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			copy->matrice[i][j] = matrice[i][j];
		}
	}
	return copy;
}