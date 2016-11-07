#ifndef GOMOKU_CONSTANTS_H
#define GOMOKU_CONSTANTS_H

#include "stdafx.h"

static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const unsigned SMOOTHING_FACTOR = 8;

static const int SIDE_CELL_COUNT = 15;
static const int CHARACTER_SIZE = 45;

static const Vector2f TEXT_POSITION(150, 100);

static const float DISTANCE_BETWEEN_LINES = 40;
static const float THICKNESS_OF_LATTICE = 2;

static const float OFFSET_AXIS = 10;
static const float SQUARE_SIDE = 20;
static const float CIRCLE_OUTLINE_SIZE = 5;
static const float CIRCLE_RADIUS = 10;

static const Color COLOR_OF_FIELD(236, 234, 190);
static const Color COLOR_OF_LINES(192, 192, 192);
static const Color BACK_GROUND_COLOR(245, 245, 220);
static const Color COLOR_OF_SQUARE(193, 135, 107);
static const Color COLOR_OF_CIRCLE(190, 189, 127);
static const Color COLOR_OF_GAMEOVER_LINE(255, 0, 0);
static const Color COLOR_OF_TEXT(207, 67, 99);

static const string REQUEST_USER = "Choose your shape!";
static const string GAME_OVER_STRING = "Game over!";
static const string FONT_PATH = "Coiny-Regular.ttf";

enum State {
	Empty = 0,
	Circle,
	Square,
};

typedef sf::Vector2f Point;

struct GameText
{
	bool wasSelectedFigure = false;
	bool IsGameOver = false;
	Font font;
	Text text;
};

struct GameCell
{
	unsigned status;
	// State == 0 => Empty
	// State == 1 => Circle
	// State == 2 => Square

	Point cellPosition;


	vector<RectangleShape> squears;
	vector<CircleShape> circles;
};

struct Field
{
	RectangleShape fieldBoarder;
	float fieldSide;
	vector<vector<GameCell>> field;
	Vector2f fieldPos;
};


struct Line
{
	vector<RectangleShape> lines;
	unsigned short int linesCount;
};

struct GameObject
{
	unsigned firstPlayerShape;
	unsigned secoundPlayerShape;
	unsigned whichPlayer;

	//Поле
	Field margin;
	//Линии
	Line fieldLines;
	//Клетки
	unsigned short int sideCellCount;
	//Квадратик
	RectangleShape squarePrototype;
	//Нулик
	CircleShape circlePrototype;
	//Линия конца игры
	vector<Point> pointsOfLine;
	Vertex gameOverLine[2];

	GameText gameText;
};

#endif