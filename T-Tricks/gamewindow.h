#ifndef	GAMEWINDOW_H
#define GAMEWINDOW_H

#include "gameboard.h"
#include <QMainWindow>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlcdnumber.h>


class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameWindow(QWidget *parent = nullptr);
	~GameWindow();

public slots:


private:
	QWidget *gameWidget;
	QGridLayout *gameLayout;

	GameBoard *board;

	QLabel *nextPiece;
	QLabel *nextP;
	QLabel *score;
	QLCDNumber *scoreLCD;
	QLabel *lines;
	QLCDNumber *linesLCD;
	QPushButton *quitButton;
	QPushButton *pauseButton;


};
#endif // MAINWINDOW_H
