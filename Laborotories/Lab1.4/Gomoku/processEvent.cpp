#include "processEvent.h"

void SeekLineAtLeftDiagonal(GameObject &object, GameCell &cell, size_t i, size_t j, unsigned playerShape)
{
	unsigned shapesAtLineCount = 1;
	object.pointsOfLine.push_back(object.margin.field.at(i).at(j).cellPosition);

	for (size_t iterator = 1; iterator <= j && iterator <= i; ++iterator)
	{
		if (object.margin.field.at(i - iterator).at(j - iterator).status == playerShape)
		{
			++shapesAtLineCount;
			object.pointsOfLine.push_back(object.margin.field.at(i - iterator).at(j - iterator).cellPosition);
		}
		else
		{
			break;
		}
	}

	for (size_t iterator = 1; iterator < object.margin.field.at(i).size() - i && iterator < object.margin.field.at(j).size() - j; ++iterator)
	{
		if (object.margin.field.at(i + iterator).at(j + iterator).status == playerShape)
		{
			++shapesAtLineCount;
			object.pointsOfLine.push_back(object.margin.field.at(i + iterator).at(j + iterator).cellPosition);
		}
		else
		{
			break;
		}
	}

	if (shapesAtLineCount < 5)
	{
		object.pointsOfLine.clear();
	}
}

void SeekLineAtRightDiagonal(GameObject &object, GameCell &cell, size_t i, size_t j, unsigned playerShape)
{
	unsigned shapesAtLineCount = 1;
	object.pointsOfLine.push_back(object.margin.field.at(i).at(j).cellPosition);

	for (size_t iterator = 1; iterator < object.margin.field.at(i).size() - j && iterator <= i; ++iterator)
	{
		if (object.margin.field.at(i - iterator).at(j + iterator).status == playerShape)
		{
			++shapesAtLineCount;
			object.pointsOfLine.push_back(object.margin.field.at(i - iterator).at(j + iterator).cellPosition);
		}
		else
		{
			break;
		}
	}

	for (size_t iterator = 1; iterator < object.margin.field.at(i).size() - i && iterator <= j; ++iterator)
	{
		if (object.margin.field.at(i + iterator).at(j - iterator).status == playerShape)
		{
			++shapesAtLineCount;
			object.pointsOfLine.push_back(object.margin.field.at(i + iterator).at(j - iterator).cellPosition);
		}
		else
		{
			break;
		}
	}

	if (shapesAtLineCount < 5)
	{
		object.pointsOfLine.clear();
	}
}

void SeekLineAtHorizontal(GameObject &object, GameCell &cell, size_t i, size_t j, unsigned playerShape)
{
	unsigned shapesAtLineCount = 1;
	object.pointsOfLine.push_back(object.margin.field.at(i).at(j).cellPosition);

	for (size_t iterator = 1; iterator < object.margin.field.at(i).size() - j; ++iterator)
	{
		if (object.margin.field.at(i).at(j + iterator).status == playerShape)//Справа
		{
			++shapesAtLineCount;
			object.pointsOfLine.push_back(object.margin.field.at(i).at(j + iterator).cellPosition);
		}
		else
		{
			break;
		}
	}

	for (size_t iterator = 1; iterator <= j; ++iterator)
	{
		if (object.margin.field.at(i).at(j - iterator).status == playerShape)//Слева
		{
			++shapesAtLineCount;
			object.pointsOfLine.push_back(object.margin.field.at(i).at(j - iterator).cellPosition);
		}
		else
		{
			break;
		}
	}

	if (shapesAtLineCount < 5)
	{
		object.pointsOfLine.clear();
	}
}

void SeekLineAtVertical(GameObject &object, GameCell &cell, size_t i, size_t j, unsigned playerShape)
{
	unsigned shapesAtLineCount = 1;
	object.pointsOfLine.push_back(object.margin.field.at(i).at(j).cellPosition);

	for (size_t iterator = 1; iterator < object.margin.field.size() - i; ++iterator)
	{
		if (object.margin.field.at(i + iterator).at(j).status == playerShape)//Снизу
		{
			++shapesAtLineCount;
			object.pointsOfLine.push_back(object.margin.field.at(i + iterator).at(j).cellPosition);
		}
		else
		{
			break;
		}
	}

	for (size_t iterator = 1; iterator <= i; ++iterator)
	{
		if (object.margin.field.at(i - iterator).at(j).status == playerShape)//Сверху
		{
			++shapesAtLineCount;
			object.pointsOfLine.push_back(object.margin.field.at(i - iterator).at(j).cellPosition);
		}
		else
		{
			break;
		}
	}

	if (shapesAtLineCount < 5)
	{
		object.pointsOfLine.clear();
	}
}

void CheckGameOverLine(GameObject &object)
{
	if (object.pointsOfLine.size() >= 5)
	{
		object.gameOverLine[0] = Vertex(Vector2f(object.pointsOfLine[0].x + DISTANCE_BETWEEN_LINES / 2, object.pointsOfLine[0].y + DISTANCE_BETWEEN_LINES / 2), Color::Black);
		object.gameOverLine[1] = Vertex(Vector2f(object.pointsOfLine[4].x + DISTANCE_BETWEEN_LINES / 2, object.pointsOfLine[4].y + DISTANCE_BETWEEN_LINES / 2), Color::Black);
		object.gameText.IsGameOver = true;
		object.gameText.text.setString(GAME_OVER_STRING);
		object.gameText.text.setPosition(Vector2f(250, 100));
	}
}

void CheckLineOfShapes(GameObject &object, GameCell &cell, size_t i, size_t j)
{
	unsigned playerShape;

	if (object.whichPlayer == 1)
	{
		playerShape = object.secoundPlayerShape;
	}
	else
	{
		playerShape = object.firstPlayerShape;
	}

	SeekLineAtHorizontal(object, cell, i, j, playerShape);
	CheckGameOverLine(object);
	
	SeekLineAtVertical(object, cell, i, j, playerShape);
	CheckGameOverLine(object);

	SeekLineAtRightDiagonal(object, cell, i, j, playerShape);
	CheckGameOverLine(object);

	SeekLineAtLeftDiagonal(object, cell, i, j, playerShape);
	CheckGameOverLine(object);
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

void ChooseShape(GameObject &object, GameCell &cell, const int &clickPositionX, const int &clickPositionY, size_t i, size_t j, unsigned playerShape)
{
	if (playerShape == State::Square)
	{
		object.margin.field.at(i).at(j).status = State::Square;
		CreateSquare(object, cell, object.margin.field.at(i).at(j).cellPosition.x, object.margin.field.at(i).at(j).cellPosition.y);
	}
	if (playerShape == State::Circle)
	{
		object.margin.field.at(i).at(j).status = State::Circle;
		CreateCircle(object, cell, object.margin.field.at(i).at(j).cellPosition.x, object.margin.field.at(i).at(j).cellPosition.y);
	}
}

void CreateShape(GameObject &object, GameCell &cell, const int &clickPositionX, const int &clickPositionY, size_t i, size_t j)
{
	if (object.whichPlayer == 1)
	{
		ChooseShape(object, cell, clickPositionX, clickPositionY, i, j, object.firstPlayerShape);
		object.whichPlayer = 2;
	}
	else
	{
		ChooseShape(object, cell, clickPositionX, clickPositionY, i, j, object.secoundPlayerShape);
		object.whichPlayer = 1;
	}
}

void ChoosingShape(GameObject &object, GameCell &cell, size_t i, size_t j)
{
	if (i == 7 && j == 6)
	{
		object.firstPlayerShape = State::Square;
		cell.circles.clear();
		cell.squears.clear();
		object.gameText.wasSelectedFigure = true;
	}

	if (i == 7 && j == 8)
	{
		object.firstPlayerShape = State::Circle;
		cell.circles.clear();
		cell.squears.clear();
		object.gameText.wasSelectedFigure = true;
	}

	if (object.firstPlayerShape == State::Square)
	{
		object.secoundPlayerShape = State::Circle;
	}
	else
	{
		object.secoundPlayerShape = State::Square;
	}
	
}

void ProcessClick(GameObject &object, GameCell &cell, const int &clickPositionX, const int &clickPositionY)
{
	for (size_t i = 0; i < object.sideCellCount; ++i)
	{
		for (size_t j = 0; j < object.sideCellCount; ++j)
		{
			if ((clickPositionX >= object.margin.field.at(i).at(j).cellPosition.x && clickPositionX < (object.margin.field.at(i).at(j).cellPosition.x + DISTANCE_BETWEEN_LINES)) &&
				(clickPositionY >= object.margin.field.at(i).at(j).cellPosition.y && clickPositionY < (object.margin.field.at(i).at(j).cellPosition.y + DISTANCE_BETWEEN_LINES)))
			{
				if (object.gameText.wasSelectedFigure)
				{
					if (object.margin.field.at(i).at(j).status == State::Empty)
					{
						CreateShape(object, cell, clickPositionX, clickPositionY, i, j);
						CheckLineOfShapes(object, cell, i, j);
					}
				}
				else
				{
					ChoosingShape(object, cell, i, j);
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
		if (!object.gameText.wasSelectedFigure)
		{
			CreateSquare(object, cell, object.margin.field.at(7).at(6).cellPosition.x, object.margin.field.at(7).at(6).cellPosition.y);
			CreateCircle(object, cell, object.margin.field.at(7).at(8).cellPosition.x, object.margin.field.at(7).at(8).cellPosition.y);
		}
		if (event.type == Event::MouseButtonPressed)
		{
			ProcessClick(object, cell, event.mouseButton.x, event.mouseButton.y);
		}
	}
}