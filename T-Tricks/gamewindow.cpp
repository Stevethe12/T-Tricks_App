#include "gamewindow.h"
using namespace std;
GameWindow::GameWindow(QWidget *parent)
	: QMainWindow(parent)
{
	gameWidget = new QWidget;

	//LAYOUT PRINCIPAL
	gameLayout = new QGridLayout;

	//BACKGROUND DE LINTERFACE
	QPixmap bkgnd("./Image/Background.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);

	//BOARD
	board = new GameBoard;
	board->loop();

	//LABEL
	nextPiece = new QLabel("Prochaine piece");
	nextP = new QLabel();
	score = new QLabel("Score");
	lines = new QLabel("Nombre de lignes");

	//LCD SCORE ET LIGNES
	scoreLCD = new QLCDNumber(5);
	scoreLCD->setSegmentStyle(QLCDNumber::Filled);
	linesLCD = new QLCDNumber(5);
	linesLCD->setSegmentStyle(QLCDNumber::Filled);

	//BOUTON DE GAME
	quitButton = new QPushButton("Quitter");
	QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

	pauseButton = new QPushButton("Pause");
	//QObject::connect(pauseButton,SIGNAL(clicked(), this, ));

	//PLACEMENT LAYOUT PRINCIPAL
	gameLayout->addWidget(board, 0, 0, 7, 1);
	gameLayout->addWidget(nextPiece, 0, 1);
	gameLayout->addWidget(nextP, 1, 1);
	gameLayout->addWidget(score, 2, 1);
	gameLayout->addWidget(scoreLCD, 3, 1);
	gameLayout->addWidget(lines, 4, 1);
	gameLayout->addWidget(linesLCD, 5, 1);
	gameLayout->addWidget(pauseButton, 6, 1);
	gameLayout->addWidget(quitButton, 7, 1);


	gameWidget->setLayout(gameLayout);
	setCentralWidget(gameWidget);
	resize(370, 550);
}

GameWindow::~GameWindow()
{
	delete pauseButton;
	delete quitButton;
	delete lines;
	delete score;
	delete nextP;
	delete nextPiece;

	delete scoreLCD;
	delete linesLCD;
	
	delete gameLayout;
	delete gameWidget;

}

