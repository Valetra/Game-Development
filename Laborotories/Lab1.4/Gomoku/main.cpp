/*Цвета и размеры взяты с сайта: http://www.artemlopatin.ru/gomoku/

 TODO:
	1) Создать функцию "исчезновения" 5-ти одинаковых фигур в ряду
	2) Начать писать AI
	3) Перенести интерфейс в игровое окно и модернизировать его 
*/
#include "stdafx.h"
#include "constants.h"
#include "init.h"



void CrossOutCells(GameObject &object, GameCell &cell, size_t i, size_t j, const float &cellPositionX, const float &cellPositionY)
{
	cout << "Cross cells\n";
	object.squarePrototype.setFillColor(COLOR_OF_GAMEOVER_LINE);
	object.squarePrototype.setSize(Vector2f(DISTANCE_BETWEEN_LINES * 4.5, 5));
	object.squarePrototype.setPosition(Vector2f(cellPositionX + OFFSET_AXIS + 3, cellPositionY + OFFSET_AXIS + 7));
	cell.squears.push_back(object.squarePrototype);
}

void IsLineAtLeftDiagonal(GameObject &object, GameCell &cell, size_t i, size_t j)
{
	unsigned shapesAtLineCount = 1;

	for (size_t iterator = 1; iterator <= j && iterator <= i; ++iterator)
	{
		if (object.margin.field.at(i - iterator).at(j - iterator).status == object.shape)
		{
			++shapesAtLineCount;
		}
		else
		{
			break;
		}
	}
	for (size_t iterator = 1; iterator < object.margin.field.at(i).size() - i && iterator < object.margin.field.at(j).size() - j; ++iterator)
	{
		if (object.margin.field.at(i + iterator).at(j + iterator).status == object.shape)
		{
			++shapesAtLineCount;
		}
		else
		{
			break;
		}
	}
	if (shapesAtLineCount >= 5)
	{
		//CrossOutCells(object, cell, i, j, object.margin.field.at(i).at(j).cellPosition.x, object.margin.field.at(i).at(j).cellPosition.y);
		cout << "По левой диагонали набралось 5 фигур\n";
	}
}

void IsLineAtRightDiagonal(GameObject &object, GameCell &cell, size_t i, size_t j)
{
	unsigned shapesAtLineCount = 1;

	for (size_t iterator = 1; iterator < object.margin.field.at(i).size() - j && iterator <= i; ++iterator)
	{
		if (object.margin.field.at(i - iterator).at(j + iterator).status == object.shape)
		{
			++shapesAtLineCount;
		}
		else
		{
			break;
		}
	}
	for (size_t iterator = 1; iterator < object.margin.field.at(i).size() - i && iterator <= j; ++iterator)
	{
		if (object.margin.field.at(i + iterator).at(j - iterator).status == object.shape)
		{
			++shapesAtLineCount;
		}
		else
		{
			break;
		}
	}
	if (shapesAtLineCount >= 5)
	{
		//CrossOutCells(object, cell, i, j, object.margin.field.at(i).at(j).cellPosition.x, object.margin.field.at(i).at(j).cellPosition.y);
		cout << "По правой диагонали набралось 5 фигур\n";
	}
}

void IsLineAtGorizontal(GameObject &object, GameCell &cell, size_t i, size_t j)
{
	unsigned shapesAtLineCount = 1;

	for (size_t iterator = 1; iterator < object.margin.field.at(i).size() - j; ++iterator)
	{

		if (object.margin.field.at(i).at(j + iterator).status == object.shape)//Справа
		{
			++shapesAtLineCount;
		}
		else
		{
			break;
		}
	}

	for (size_t iterator = 1; iterator <= j; ++iterator)
	{
		if (object.margin.field.at(i).at(j - iterator).status == object.shape)//Слева
		{
			++shapesAtLineCount;
		}
		else
		{
			break;
		}
	}

	if (shapesAtLineCount >= 5)
	{
		//CrossOutCells(object, cell, i, j, object.margin.field.at(i).at(j).cellPosition.x, object.margin.field.at(i).at(j).cellPosition.y);
		cout << "По горизонтали набралось 5 фигур\n";
	}
}

void IsLineAtVertical(GameObject &object, GameCell &cell, size_t i, size_t j)
{
	unsigned shapesAtLineCount = 1;
	for (size_t iterator = 1; iterator < object.margin.field.size() - i; ++iterator)
	{
		if (object.margin.field.at(i + iterator).at(j).status == object.shape)//Снизу
		{
			++shapesAtLineCount;
		}
		else
		{
			break;
		}
	}
	for (size_t iterator = 1; iterator <= i; ++iterator)
	{
		if (object.margin.field.at(i - iterator).at(j).status == object.shape)//Сверху
		{
			++shapesAtLineCount;
		}
		else
		{
			break;
		}
	}

	if (shapesAtLineCount >= 5)
	{
		//CrossOutCells(object, cell, i, j, object.margin.field.at(i).at(j).cellPosition.x, object.margin.field.at(i).at(j).cellPosition.y);
		cout << "По вертикали набралось 5 фигур\n";
	}
}

void CheckLineOfShapes(GameObject &object, GameCell &cell, size_t i, size_t j)
{
	IsLineAtGorizontal(object, cell, i, j);
	IsLineAtVertical(object, cell, i, j);
	IsLineAtRightDiagonal(object, cell, i, j);
	IsLineAtLeftDiagonal(object, cell, i, j);
}

void CreateSquare(GameObject &object, GameCell &cell, const float &cellPositionX, const float &cellPositionY)
{
	object.squarePrototype.setFillColor(COLOR_OF_SQUARE);
	object.squarePrototype.setSize(Vector2f(SQUARE_SIDE, SQUARE_SIDE));
	object.squarePrototype.setPosition(Vector2f(cellPositionX + OFFSET_AXIS, cellPositionY + OFFSET_AXIS));
	cell.squears.push_back(object.squarePrototype);
}

void CreateCircle(GameObject &object, GameCell &cell, const float &cellPositionX, const float &cellPositionY)
{
	object.circlePrototype.setFillColor(COLOR_OF_FIELD);
	object.circlePrototype.setOutlineColor(COLOR_OF_CIRCLE);
	object.circlePrototype.setOutlineThickness(CIRCLE_OUTLINE_SIZE);
	object.circlePrototype.setPosition(Vector2f(cellPositionX + OFFSET_AXIS, cellPositionY + OFFSET_AXIS));
	object.circlePrototype.setRadius(CIRCLE_RADIUS);
	cell.circles.push_back(object.circlePrototype);
}

void ProcessClick(GameObject &object, GameCell &cell, const int &clickPositionX, const int &clickPositionY)
{
	for (size_t i = 0; i < object.sideCellCount; ++i)
	{
		for (size_t j = 0; j < object.sideCellCount; ++j)
		{
			if ((clickPositionX >= object.margin.field.at(i).at(j).cellPosition.x && clickPositionX < (object.margin.field.at(i).at(j).cellPosition.x + DISTANCE_BETWEEN_LINES))&&
				(clickPositionY >= object.margin.field.at(i).at(j).cellPosition.y && clickPositionY < (object.margin.field.at(i).at(j).cellPosition.y + DISTANCE_BETWEEN_LINES)))
			{
				//Смена статуса нажатой клетки
				if (object.margin.field.at(i).at(j).status == State::Empty)
				{
					
					if (object.shape == State::Square)
					{
						object.margin.field.at(i).at(j).status = State::Square;
						CreateSquare(object, cell, object.margin.field.at(i).at(j).cellPosition.x, object.margin.field.at(i).at(j).cellPosition.y);
					}
					if (object.shape == State::Circle)
					{
						object.margin.field.at(i).at(j).status = State::Circle;
						CreateCircle(object, cell, object.margin.field.at(i).at(j).cellPosition.x, object.margin.field.at(i).at(j).cellPosition.y);
					}
					CheckLineOfShapes(object, cell, i, j);
				}
			}
		}
	}
}

void ProcessEvent(GameObject &object, GameCell &cell, Event &event, RenderWindow &window)
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
		if (event.type == Event::MouseButtonPressed)
		{
			ProcessClick(object, cell, event.mouseButton.x, event.mouseButton.y);
		}
	}
}












void DrawCircle(RenderWindow &window, GameCell &cell)
{
	for (size_t i = 0; i < cell.circles.size(); ++i)
	{
		window.draw(cell.circles.at(i));
	}
}

void DrawSquare(RenderWindow &window, GameCell &cell)
{
	for (size_t i = 0; i < cell.squears.size(); ++i)
	{
		window.draw(cell.squears.at(i));
	}	
}

void DrawField(RenderWindow &window, GameObject &object)
{
	window.draw(object.margin.fieldBoarder);
}

void DrawCells(RenderWindow &window, GameObject &object)
{
	for (size_t i = 0; i < object.line.lines.size(); ++i)
	{
		window.draw(object.line.lines.at(i));
	}
}

void DrawObjects(RenderWindow &window, GameObject &object, GameCell &cell)
{
	DrawField(window, object);
	DrawCells(window, object);
	DrawCircle(window, cell);
	DrawSquare(window, cell);
}

int RequestUser(GameCell &cell, GameObject &object)
{
	cout << "Выберите фигуру квадрат или нолик (2 - квадрат || 1 - нолик )\n";
	cin >> object.shape;
	if (object.shape < 1 || object.shape > 2)
	{
		cout << "Глупец!";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void GameLoop(RenderWindow &window, GameObject &object, GameCell &cell)
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
	GameObject object;
	GameCell cell;
	ContextSettings settings;

	if (RequestUser(cell, object) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}
	
	InitSettings(settings);
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gomoku", Style::Default, settings);
	SetField(object, cell, window);

	GameLoop(window, object, cell);
	return EXIT_SUCCESS;
}