#include "gameboard.h"


#define FLECHE_GAUCHE 75
#define FLECHE_DROITE 77
#define FLECHE_HAUT 72
#define FLECHE_BAS 80

using namespace std;

GameBoard::GameBoard(QWidget *parent)
	: QFrame(parent)
{
	setFrameStyle(QFrame::Panel | QFrame::Sunken);
	setFocusPolicy(Qt::StrongFocus);

	srand(time(NULL));
	curForme = new GameForme(rand() % FORMEZ);
	prochaineForme = new GameForme(rand() % FORMEZ);

	curForme->setX(4);
	curForme->setY(2);
	lastAction = std::chrono::high_resolution_clock::now();
	alive = true;
	score = 0;
	linesCleared = 0;
}
GameBoard::~GameBoard()
{
	delete curForme;
}

QSize GameBoard::sizeHint() const
{
	return QSize(LARGEUR * 15, HAUTEUR * 15);
}

QSize GameBoard::minimumSizeHint() const
{
	return QSize(LARGEUR * 5, HAUTEUR * 5);
}

void GameBoard::paintEvent(QPaintEvent *event)
{
	QFrame::paintEvent(event);

	QPainter painter(this);
	QRect rectangle = contentsRect();
	int boardTop = rectangle.bottom() - HAUTEUR * squareHeight();
	preview = curForme->copy();
	preview->setPreview(true);
	bougerForme(preview, 0, 23);
	for (int i = 0; i < HAUTEUR; i++)
	{
		for (int j = 0; j < LARGEUR; j++)
		{
			if (curForme->getTileGlobal(i, j) == 1)
			{
				drawSquare(painter, rectangle.left() + j * squareWidth(), boardTop + i * squareHeight(), curForme);
			}
			else
			{

			}

		}
	}
}

//void GameBoard::afficher()
//{
//	preview = curForme->copy();
//	preview->setPreview(true);
//	bougerForme(preview, 0, 23);
//	for (int i = 0; i < HAUTEUR; i++)
//	{
//		for (int j = 0; j < LARGEUR; j++)
//		{
//			if (board[i][j] == 1 || curForme->getTileGlobal(i, j) == 1)
//			{
//				drawSquare(painter, rect.left() + j * squareWidth(), boardTop + i * squareHeight(), );
//			}
//			else if (preview->getTileGlobal(i, j) == 1)
//			{
//				cout << "o";
//			}
//			else
//			{
//				cout << " ";
//			}
//		}
//	}
//	cout << "______" << "Level: " << level.getLevelNumber() << '\n';
//	cout << "Lines cleared: " << linesCleared;
//	cout << flush;
//	delete preview;
//}

bool GameBoard::collision(GameForme *forme)
{
	int xCentreForme = forme->getX();
	int yCentreForme = forme->getY();
	int xGlobal;
	int yGlobal;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			xGlobal = xCentreForme + (j - 2);
			yGlobal = yCentreForme + (i - 2);
			if (forme->getTile(i, j) == 1 && (board[yGlobal][xGlobal] == 1 || yGlobal > 23 || xGlobal < 0 || xGlobal > 9))
			{
				cout << "xGlobal: " << xGlobal << endl;
				return true;
			}
		}
	}

	return false;
}

void GameBoard::ligneComplete()
{
	int lignePleine = 1;
	int nmbLignes = 0;
	for (int i = 0; i < HAUTEUR; i++)
	{
		lignePleine = 1;
		for (int j = 0; j < LARGEUR; j++)
		{
			if (board[i][j] != 1)
			{
				lignePleine = 0;
			}
		}
		if (lignePleine == 1)
		{
			shiftBoard(i);
			nmbLignes++;
			i--;
		}
	}
	score += level.getScore(nmbLignes);
	linesCleared += nmbLignes;
}
void GameBoard::shiftBoard(int index)
{
	for (int i = index; i > 0; i--)
	{
		for (int j = 0; j < LARGEUR; j++)
		{
			board[i][j] = board[i - 1][j];
		}
	}
}

void GameBoard::mort()
{
	if (curForme->getY() < 3 && collision(curForme) == true)
	{
		alive = false;
	}
}

void GameBoard::input()
{
	if (_kbhit())
	{
		int pressedChar;
		pressedChar = _getch();
		switch (pressedChar)
		{
		case FLECHE_HAUT:
			tournerForme(curForme);
			//paintEvent();
			break;
		case FLECHE_DROITE:
			bougerForme(curForme, 1, 0);
			//paintEvent();
			break;
		case FLECHE_GAUCHE:
			bougerForme(curForme, -1, 0);
			//paintEvent();
			break;
		case FLECHE_BAS:
			bougerForme(curForme, 0, 23);
			//paintEvent();
			break;
		}
	}
}
void GameBoard::bougerForme(GameForme *forme, int x, int y)
{
	int xInitial = forme->getX();
	int yInitial = forme->getY();
	if (x > 0)
	{

		for (int i = 0; i <= x; i++)
		{
			forme->setX(xInitial + i);
			if (collision(forme) == true)
			{
				forme->setX(xInitial + i - 1);
				break;
			}
		}
	}
	else if (x < 0)
	{
		for (int i = 0; i >= x; i--)
		{
			forme->setX(xInitial + i);
			if (collision(forme) == true)
			{
				forme->setX(xInitial + i + 1);
				break;
			}
		}
	}
	for (int i = 0; i <= y; i++)
	{
		forme->setY(yInitial + i);
		if (collision(forme) == true)
		{
			forme->setY(yInitial + i - 1);
			if (!forme->isPreview())
			{
				formeVersBoard(forme);
				changerForme();
			}
			break;
		}
	}

}

void GameBoard::changerForme()
{
	int typeProchaineForme;
	delete curForme;
	curForme = prochaineForme;
	typeProchaineForme = rand() % FORMEZ;
	if (typeProchaineForme == curForme->getType())
	{
		typeProchaineForme == rand() % FORMEZ;
	}
	prochaineForme = new GameForme(typeProchaineForme);
}

void GameBoard::tournerForme(GameForme *forme)
{
	tournerForme(forme, DROITE);
}

void GameBoard::tournerForme(GameForme *forme, int direction)
{
	forme->tourner(direction);
	if (collision(forme) == true)
	{
		forme->tourner(direction * -1);
	}
}

void GameBoard::formeVersBoard(GameForme *forme)
{
	int xforme = forme->getX();
	int yforme = forme->getY();

	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (forme->getTile(i, j) == 1)
			{
				board[yforme + (i - 2)][xforme + (j - 2)] = forme->getTile(i, j);
			}
		}
	}
}

void GameBoard::loop()
{
	
	while (alive)
	{
		input();
		//level.update(linesCleared);
		if (true)
		{
			bougerForme(curForme, 0, 1);
			//paintEvent();
			ligneComplete();
			//paintEvent();
			mort();
			level.update(linesCleared);
			
		}
	}
	cout << "GAME OVER" << endl;
}


void GameBoard::drawSquare(QPainter &painter, int x, int y, GameForme *forme)
{
	static constexpr QRgb colorTable[8] = {
		0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
		0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
	};

	QColor color = colorTable[int(forme->getX()), int(forme->getY())];
	painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
		color);

	painter.setPen(color.lighter());
	painter.drawLine(x, y + squareHeight() - 1, x, y);
	painter.drawLine(x, y, x + squareWidth() - 1, y);

	painter.setPen(color.darker());
	painter.drawLine(x + 1, y + squareHeight() - 1,
		x + squareWidth() - 1, y + squareHeight() - 1);
	painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
		x + squareWidth() - 1, y + 1);
}

