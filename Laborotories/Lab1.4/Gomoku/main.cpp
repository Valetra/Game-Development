//TODO: Процесс обработки зависимости размера поля от кол-ва клеток и т.п..

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

static const unsigned DISTANCE_BETWEEN_LINES = 40;
static const unsigned LINES_COUNT = 28;
static const float FIELD_SIDE = 600;
static const unsigned THICKNESS_OF_LATTICE = 2;
static const unsigned DEFAULT_CELLS_COUNT = 5;

static const Color COLOR_OF_FIELD(236, 234, 190);
static const Color COLOR_OF_LINES(192, 192, 192);

struct Objects
{
	//Поле
	RectangleShape field;
	//Клетки
	RectangleShape lines[DEFAULT_CELLS_COUNT];
};

void ProcessEvent(Event &event, RenderWindow &window)
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
}

void CreateGameField(Objects &object, RenderWindow &window, float fieldPosX, float fieldPosY)
{
	object.field.setSize(Vector2f(FIELD_SIDE, FIELD_SIDE));

	Vector2f fieldPos(fieldPosX, fieldPosY);
	object.field.setPosition(fieldPos);

	object.field.setFillColor(COLOR_OF_FIELD);
	object.field.setOutlineColor(COLOR_OF_LINES);
	object.field.setOutlineThickness(THICKNESS_OF_LATTICE);
}

void CreateGameCells(Objects &object, float fieldPosX, float fieldPosY)
{
	for (int i = 0, j = 0; i < LINES_COUNT; ++i)
	{

		object.lines[i].setFillColor(COLOR_OF_LINES);
		if (i < 14)
		{
			object.lines[i].setSize(Vector2f(THICKNESS_OF_LATTICE, FIELD_SIDE));
			object.lines[i].setPosition(fieldPosX + DISTANCE_BETWEEN_LINES * (i + 1), fieldPosY);
		}
		else
		{
			object.lines[i].setSize(Vector2f(FIELD_SIDE, THICKNESS_OF_LATTICE));
			object.lines[i].setPosition(fieldPosX, fieldPosY + DISTANCE_BETWEEN_LINES * (j + 1));
			++j;
		}
	}
}

void CreateGameTable(Objects &object, RenderWindow &window)
{
	Vector2u size = window.getSize();
	float fieldPosX = size.x / 2 - FIELD_SIDE / 2;
	float fieldPosY = size.y / 2 - FIELD_SIDE / 2;

	CreateGameField(object, window, fieldPosX, fieldPosY);
	CreateGameCells(object, fieldPosX, fieldPosY);
}

void DrawField(RenderWindow &window, Objects &objects)
{
	window.draw(objects.field);
}

void DrawCells(RenderWindow &window, Objects &objects)
{
	for (size_t i = 0; i < LINES_COUNT; ++i)
	{
		window.draw(objects.lines[i]);
	}
}

void DrawObjects(RenderWindow &window, Objects &objects)
{
	DrawField(window, objects);
	DrawCells(window, objects);
}

int main()
{
	unsigned cellSideCount;
	cout << "Введите размер поля от 5 до 15 включительно\n";
	cin >> cellSideCount;
	if (cellSideCount < 5 && cellSideCount > 15)
	{
		cout << "Плохиш!\n";
		return 1;
	}
	unsigned linesCount = (cellSideCount - 1) * 2;

	RenderWindow window(VideoMode(1024, 768), "Gomoku", Style::Fullscreen);
	Color backGroundColor(245, 245, 220);
	Objects objects;
	


	//Game Loop
	while (window.isOpen())
	{
		Event event;
		//Обработка событий
		ProcessEvent(event, window);
		
		//Очистка экрана
		window.clear(backGroundColor);

		//Установка поля
		CreateGameTable(objects, window);
		//Установка крестиков ноликов в положения
		//Отрисовка изображения
		DrawObjects(window, objects);
		window.display();
	}
	return 0;
}