#include <iostream>
#include <math.h>
#include <cmath>

static const double G = 9.8;
static const int MAX_HEIGHT = 50;

using namespace std;

bool isValidHight(int height)
{
	return (height >= 0 && height <= MAX_HEIGHT);
}

int main(int, char *[])
{
	setlocale(LC_ALL, "rus");
	int maxHeight;
	double currentHeight;
	bool isMaxHeight = false;

	// Вывод максимально возможной высоты прыжка
	cout << "Максимально возможная высота прыжка = " << MAX_HEIGHT << '\n';
	cout << "Введите высоту вашего прыжка: ";
	cin >> maxHeight;
	printf("\n");
	double timeAtMaxHeight = sqrt(maxHeight * 2 / G);
	double initialSpeed = G * timeAtMaxHeight;
	if (!isValidHight(maxHeight))
	{
		cout << "Введите целое число от 0 до " << MAX_HEIGHT << '\n';
		return 1;
	}

	for (double currentTime = 0; currentTime < timeAtMaxHeight * 2; currentTime += 0.1f)
	{
		if (!isMaxHeight && currentTime > timeAtMaxHeight)
		{
			isMaxHeight = true;
			currentHeight = initialSpeed * timeAtMaxHeight - 0.5f * G * pow(timeAtMaxHeight, 2);
			cout << "Время достигаетижения максимальной высоты =" << timeAtMaxHeight << " Текущая высота = " << currentHeight << '\n';
		}
		currentHeight = initialSpeed * currentTime - 0.5f * G * pow(currentTime, 2);
		cout << "Текущее время = " << currentTime << " Текущая высота = " << currentHeight << '\n';
	}

	currentHeight = initialSpeed * (timeAtMaxHeight * 2) - 0.5f * G * pow(timeAtMaxHeight * 2, 2);
	cout << "Время достигаетижения максимальной высоты =" << timeAtMaxHeight * 2 << "\nТекущая высота = " << currentHeight << '\n';
	return 0;
}