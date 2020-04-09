#include <qmainwindow.h>
#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <qpainter.h>
#include <qframe.h>
#include <QBasicTimer>
#include "gameforme.h"
#include "gamelevel.h"
#define LARGEUR 10
#define HAUTEUR 24 

class GameBoard : public QFrame
{
	Q_OBJECT

public:
	GameBoard(QWidget *parent = nullptr);
	~GameBoard();

	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;
	//void nextPieceLabel(QLabel *label);
	GameForme *curForme;
	QBasicTimer timer;

	bool collision(GameForme *forme);
	void ligneComplete();
	void shiftBoard(int index);
	void input();
	void mort();
	void bougerForme(GameForme *forme, int x, int y);
	void changerForme();
	void tournerForme(GameForme *forme);
	void tournerForme(GameForme *forme, int direction);
	void formeVersBoard(GameForme *forme);
	void loop();

public slots:
	//void pauseGame();

signals:
	void changerScore(int score);
	//void changerlines(int nbrLines);
	
protected:
	void paintEvent(QPaintEvent *event) override;

private:
	int squareWidth() { return contentsRect().width() / LARGEUR; }
	int squareHeight() { return contentsRect().height() / HAUTEUR; }
	void drawSquare(QPainter &painter, int x, int y, GameForme *forme);
	
	
	GameForme *preview;
	GameForme *prochaineForme;
	GameLevel level;

	int board[HAUTEUR][LARGEUR] = { 0 };
	int score;
	int linesCleared;
	bool alive;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastAction, curTime;


};
