#include "render.h"

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