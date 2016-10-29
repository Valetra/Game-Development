#include "constants.h"
#include "init.h"

void InitSettings(ContextSettings &settings)
{
	settings.antialiasingLevel = SMOOTHING_FACTOR;
}

void InitCell(GameObject &object, GameCell &cage, const  size_t &i, const  size_t &j)
{
	cage.cellPosition.x = object.margin.fieldPosX + j * DISTANCE_BETWEEN_LINES;
	cage.cellPosition.y = object.margin.fieldPosY + i * DISTANCE_BETWEEN_LINES;
	cage.status = State::Empty;
}

void InitField(GameCell &cell, GameObject &object)
{
	object.margin.field.resize(object.sideCellCount);
	for (size_t i = 0; i < object.sideCellCount; ++i)
	{
		for (size_t j = 0; j < object.sideCellCount; ++j)
		{
			GameCell cage;
			InitCell(object, cage, i, j);
			object.margin.field.at(i).push_back(cage);
		}
	}
}

void CreateGameCells(GameObject &object)
{
	for (size_t i = 0, j = 0; i < object.line.lines.size(); ++i)
	{
		// TODO: move to reference variable `object.line.lines.at(i)`
		object.line.lines.at(i).setFillColor(COLOR_OF_LINES);
		if (i < object.line.lines.size() / 2)
		{
			object.line.lines.at(i).setSize(Vector2f(THICKNESS_OF_LATTICE, object.margin.fieldSide));
			object.line.lines.at(i).setPosition(object.margin.fieldPosX + DISTANCE_BETWEEN_LINES * (i + 1), object.margin.fieldPosY);
		}
		else
		{
			object.line.lines.at(i).setSize(Vector2f(object.margin.fieldSide, THICKNESS_OF_LATTICE));
			object.line.lines.at(i).setPosition(object.margin.fieldPosX, object.margin.fieldPosY + DISTANCE_BETWEEN_LINES * (j + 1));
			++j;
		}
	}
}

void CreateFieldBoarder(GameObject &object, RenderWindow &window)
{
	object.margin.fieldBoarder.setSize(Vector2f(object.margin.fieldSide, object.margin.fieldSide));

	Vector2f fieldPos(object.margin.fieldPosX, object.margin.fieldPosY);
	object.margin.fieldBoarder.setPosition(fieldPos);

	object.margin.fieldBoarder.setFillColor(COLOR_OF_FIELD);
	object.margin.fieldBoarder.setOutlineColor(COLOR_OF_LINES);
	object.margin.fieldBoarder.setOutlineThickness(THICKNESS_OF_LATTICE);
}

void CreateGameField(GameObject &object, RenderWindow &window, GameCell &cell)
{
	Vector2u size = window.getSize();
	object.margin.fieldPosX = size.x / 2 - object.margin.fieldSide / 2;
	object.margin.fieldPosY = size.y / 2 - object.margin.fieldSide / 2;

	InitField(cell, object);

	CreateFieldBoarder(object, window);
	CreateGameCells(object);
}

void SetField(GameObject &object, GameCell &cell, RenderWindow &window)
{
	object.sideCellCount = SIDE_CELL_COUNT;
	object.margin.fieldSide = object.sideCellCount * DISTANCE_BETWEEN_LINES;
	object.line.linesCount = (object.sideCellCount - 1) * 2;
	object.line.lines.resize(object.line.linesCount);
	CreateGameField(object, window, cell);
}