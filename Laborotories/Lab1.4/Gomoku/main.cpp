/*Цвета и размеры взяты с сайта: http://www.artemlopatin.ru/gomoku/

 TODO:
	1) Создать функцию "исчезновения" 5-ти одинаковых фигур в ряду
	2) Начать писать AI
	3) Перенести и модернизировать интерфейс в игровое окно
*/

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

static const unsigned WINDOW_WIDTH = 1366;
static const unsigned WINDOW_HEIGHT = 768;

static const int MIN_SIDE_CELL_COUNT = 5;
static const int MAX_SIDE_CELL_COUNT = 15;

static const float DISTANCE_BETWEEN_LINES = 40;
static const float THICKNESS_OF_LATTICE = 2;

static const float OFFSET_AXIS = 10;
static const float SQUARE_SIDE = 20;
static const float CIRCLE_OUTLINE_SIZE = 5;
static const float CIRCLE_RADIUS = 10;

static const Color COLOR_OF_FIELD(236, 234, 190);
static const Color COLOR_OF_LINES(192, 192, 192);
static const Color BACK_GROUND_COLOR(245, 245, 220);
static const Color COLOR_OF_CROSS(193, 135, 107);
static const Color COLOR_OF_CIRCLE(190, 189, 127);

static const int CELL_STATUS_SQUARE = 1;
static const int CELL_STATUS_CIRCLE = 0;
static const int CELL_STATUS_EMPTY = -1;

struct Point
{
	float x;
	float y;
};

struct Cell
{
	int status;
	
	Point cellPosition;

	vector<RectangleShape> squears;
	vector<CircleShape> circles;
};

struct Object
{
	unsigned shape;
	//Поле
	RectangleShape fieldBoarder;
	float fieldSide;
	vector<vector<Cell>> field;
	float fieldPosX;
	float fieldPosY;
	//Линии
	vector<RectangleShape> lines;
	unsigned short int linesCount;
	//Клетки
	unsigned short int sideCellCount;
	//Квадратик
	RectangleShape square;
	//Нулик
	CircleShape circle;
};

void InitSettings(ContextSettings &settings)
{
	settings.antialiasingLevel = 8;
}

void CreateSquare(Object &object, Cell &cell, const float &cellPositionX, const float &cellPositionY)
{
	object.square.setFillColor(COLOR_OF_CROSS);
	object.square.setSize(Vector2f(SQUARE_SIDE, SQUARE_SIDE));
	object.square.setPosition(Vector2f(cellPositionX + OFFSET_AXIS, cellPositionY + OFFSET_AXIS));
	cell.squears.push_back(object.square);
}

void CreateCircle(Object &object, Cell &cell, const float &cellPositionX, const float &cellPositionY)
{
	object.circle.setFillColor(COLOR_OF_FIELD);
	object.circle.setOutlineColor(COLOR_OF_CIRCLE);
	object.circle.setOutlineThickness(CIRCLE_OUTLINE_SIZE);
	object.circle.setPosition(Vector2f(cellPositionX + OFFSET_AXIS, cellPositionY + OFFSET_AXIS));
	object.circle.setRadius(CIRCLE_RADIUS);
	cell.circles.push_back(object.circle);
}

void ProcessClickPosition(Object &object, Cell &cell, const int &clickPositionX, const int &clickPositionY)
{
	for (size_t i = 0; i < object.sideCellCount; ++i)
	{
		for (size_t j = 0; j < object.sideCellCount; ++j)
		{
			if ((clickPositionX >= object.field.at(i).at(j).cellPosition.x && clickPositionX < (object.field.at(i).at(j).cellPosition.x + DISTANCE_BETWEEN_LINES))&&
				(clickPositionY >= object.field.at(i).at(j).cellPosition.y && clickPositionY < (object.field.at(i).at(j).cellPosition.y + DISTANCE_BETWEEN_LINES)))
			{
				//Смена статуса
				if (object.field.at(i).at(j).status == CELL_STATUS_EMPTY)
				{
					if (object.shape == CELL_STATUS_SQUARE)
					{
						object.field.at(i).at(j).status = CELL_STATUS_SQUARE;
						CreateSquare(object, cell, object.field.at(i).at(j).cellPosition.x, object.field.at(i).at(j).cellPosition.y);
					}
					if (object.shape == CELL_STATUS_CIRCLE)
					{
						object.field.at(i).at(j).status = CELL_STATUS_CIRCLE;
						CreateCircle(object, cell, object.field.at(i).at(j).cellPosition.x, object.field.at(i).at(j).cellPosition.y);
					}
				}
			}
		}
	}
}

void ProcessEvent(Object &object, Cell &cell, Event &event, RenderWindow &window)
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
		if (event.type == Event::MouseButtonPressed)
		{
			ProcessClickPosition(object, cell, event.mouseButton.x, event.mouseButton.y);
		}
	}
}

void CreateFieldBoarder(Object &object, RenderWindow &window)
{
	object.fieldBoarder.setSize(Vector2f(object.fieldSide, object.fieldSide));

	Vector2f fieldPos(object.fieldPosX, object.fieldPosY);
	object.fieldBoarder.setPosition(fieldPos);

	object.fieldBoarder.setFillColor(COLOR_OF_FIELD);
	object.fieldBoarder.setOutlineColor(COLOR_OF_LINES);
	object.fieldBoarder.setOutlineThickness(THICKNESS_OF_LATTICE);
}

void CreateGameCells(Object &object)
{
	for (size_t i = 0, j = 0; i < object.lines.size(); ++i)
	{
		object.lines.at(i).setFillColor(COLOR_OF_LINES);
		if (i < object.lines.size() / 2)
		{
			object.lines.at(i).setSize(Vector2f(THICKNESS_OF_LATTICE, object.fieldSide));
			object.lines.at(i).setPosition(object.fieldPosX + DISTANCE_BETWEEN_LINES * (i + 1), object.fieldPosY);
		}
		else
		{
			object.lines.at(i).setSize(Vector2f(object.fieldSide, THICKNESS_OF_LATTICE));
			object.lines.at(i).setPosition(object.fieldPosX, object.fieldPosY + DISTANCE_BETWEEN_LINES * (j + 1));
			++j;
		}
	}
}

void InitCell(Object &object, Cell &cage, const  size_t &i, const  size_t &j)
{
	cage.cellPosition.x = object.fieldPosX + j * DISTANCE_BETWEEN_LINES;
	cage.cellPosition.y = object.fieldPosY + i * DISTANCE_BETWEEN_LINES;
	cage.status = CELL_STATUS_EMPTY;
}


void InitField(Cell &cell, Object &object)
{
	object.field.resize(object.sideCellCount);

	for (size_t i = 0; i < object.sideCellCount; ++i)
	{
		for (size_t j = 0; j < object.sideCellCount; ++j)
		{
			Cell cage;
			InitCell(object, cage, i, j);
			object.field.at(i).push_back(cage);
		}
	}
}

void CreateGameField(Object &object, RenderWindow &window, Cell &cell)
{
	Vector2u size = window.getSize();
	object.fieldPosX = size.x / 2 - object.fieldSide / 2;
	object.fieldPosY = size.y / 2 - object.fieldSide / 2;

	InitField(cell, object);

	CreateFieldBoarder(object, window);
	CreateGameCells(object);
}

void DrawCircle(RenderWindow &window, Cell &cell)
{
	for (size_t i = 0; i < cell.circles.size(); ++i)
	{
		window.draw(cell.circles.at(i));
	}
}

void DrawSquare(RenderWindow &window, Cell &cell)
{
	for (size_t i = 0; i < cell.squears.size(); ++i)
	{
		window.draw(cell.squears.at(i));
	}	
}

void DrawField(RenderWindow &window, Object &object)
{
	window.draw(object.fieldBoarder);
}

void DrawCells(RenderWindow &window, Object &object)
{
	for (size_t i = 0; i < object.lines.size(); ++i)
	{
		window.draw(object.lines.at(i));
	}
}

void DrawObjects(RenderWindow &window, Object &object, Cell &cell)
{
	DrawField(window, object);
	DrawCells(window, object);
	DrawSquare(window, cell);
	DrawCircle(window, cell);
}

int UserRequest(Cell &cell, Object &object)
{
	cout << "Введите размер поля от 5 до 15 включительно\n";
	cin >> object.sideCellCount;
	if (object.sideCellCount < MIN_SIDE_CELL_COUNT || object.sideCellCount > MAX_SIDE_CELL_COUNT)
	{
		cout << "Плохиш!\n";
		return EXIT_FAILURE;
	}
	cout << "Выберите фигуру квадрат или нолик (1 - квадрат || 0 - нолик )\n";
	cin >> object.shape;
	return EXIT_SUCCESS;
}



void SetField(Object &object, Cell &cell, RenderWindow &window)
{
	object.fieldSide = object.sideCellCount * DISTANCE_BETWEEN_LINES;
	object.linesCount = (object.sideCellCount - 1) * 2;
	object.lines.resize(object.linesCount);
	CreateGameField(object, window, cell);
}

void GameLoop(RenderWindow &window, Object &object, Cell &cell)
{
	while (window.isOpen())
	{
		Event event;
		ProcessEvent(object, cell, event, window);
		window.clear(BACK_GROUND_COLOR);
		DrawObjects(window, object, cell);
		window.display();
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	Object object;
	Cell cell;
	ContextSettings settings;

	if (UserRequest(cell, object) == EXIT_FAILURE)
	{
		return EXIT_SUCCESS;
	}
	
	InitSettings(settings);
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gomoku", Style::Fullscreen, settings);
	SetField(object, cell, window);

	GameLoop(window, object, cell);
	return EXIT_SUCCESS;
}