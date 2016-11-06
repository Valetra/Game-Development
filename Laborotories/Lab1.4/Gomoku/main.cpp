/*Цвета и размеры взяты с сайта: http://www.artemlopatin.ru/gomoku/

 TODO:
	1) Создать функцию "зачеркинвания" 5-ти одинаковых фигур в ряду
	2) Написать AI
	3) Перенести интерфейс в игровое окно и модернизировать его 
*/
#include "stdafx.h"
#include "constants.h"
#include "init.h"
#include "render.h"
#include "processEvent.h"

int RequestUser(GameObject &object)
{
	cout << "Выберите фигуру квадрат или нолик (1 - нолик || 2 - квадрат )\n";
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

	if (RequestUser(object) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}
	
	InitSettings(settings);
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gomoku", Style::Default, settings);
	SetField(object, cell, window);

	GameLoop(window, object, cell);
	return EXIT_SUCCESS;
}