#include "stdafx.h"
#include "constants.h"
#include "init.h"
#include "render.h"
#include "processEvent.h"

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

	object.whichPlayer = 1;
	
	InitSettings(settings);
	InitText(object.gameText.text, object.gameText.font);
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gomoku", Style::Close, settings);
	SetField(object, cell, window);

	GameLoop(window, object, cell);
	return EXIT_SUCCESS;
}