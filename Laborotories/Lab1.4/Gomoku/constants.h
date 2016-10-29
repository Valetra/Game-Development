#include "stdafx.h"

static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const unsigned SMOOTHING_FACTOR = 8;

static const int SIDE_CELL_COUNT = 15;

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

enum State {
	Empty = 0,
	Circle,
	Square,
};

typedef sf::Vector2f Point;

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
	// TODO: use sf::Vector2f
	float fieldPosX;
	float fieldPosY;
};

struct Line
{
	vector<RectangleShape> lines;
	unsigned short int linesCount;
};

struct GameObject
{
	unsigned shape;
	//Поле
	Field margin;
	//Линии
	Line line;
	//Клетки
	unsigned short int sideCellCount;
	//Квадратик
	RectangleShape squarePrototype;
	//Нулик
	CircleShape circlePrototype;
};