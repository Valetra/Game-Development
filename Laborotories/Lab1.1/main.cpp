#include <iostream>
#include <math.h>
#include <cmath>

static const double G = 9.8;
static const int MAX_HEIGHT = 50;

using namespace std;

bool IsValidHight(int height)
{
	return (height >= 0 && height <= MAX_HEIGHT);
}

void HeightCalculating(double &currentHeight, double &initialSpeed, double &currentTime, bool isMaxHeight, bool &maxHeightWas)
{
	currentHeight = initialSpeed * currentTime - 0.5f * G * pow(currentTime, 2);
	if (isMaxHeight && !maxHeightWas)
	{
		cout << "Время достигаетижения максимальной высоты =" << currentTime << " Текущая высота = " << currentHeight << '\n';
		maxHeightWas = true;
	}
	else
	{
		cout << "Текущее время = " << currentTime << " Текущая высота = " << currentHeight << '\n';
	}

}

void ProcessJump(double timeAtMaxHeight, double initialSpeed, double currentHeight, bool isMaxHeight, bool maxHeightWas)
{
	for (double currentTime = 0; currentTime < timeAtMaxHeight * 2; currentTime += 0.1f)
	{
		if (!isMaxHeight && currentTime > timeAtMaxHeight)
		{
			isMaxHeight = true;
			HeightCalculating(currentHeight, initialSpeed, timeAtMaxHeight, isMaxHeight, maxHeightWas);
		}
		HeightCalculating(currentHeight, initialSpeed, currentTime, isMaxHeight, maxHeightWas);
	}
	currentHeight = initialSpeed * (timeAtMaxHeight * 2) - 0.5f * G * pow(timeAtMaxHeight * 2, 2);
	cout << "Время достигаетижения максимальной высоты =" << timeAtMaxHeight * 2 << "\nТекущая высота = " << currentHeight << '\n';
}

int main(int, char *[])
{
	setlocale(LC_ALL, "rus");
	double currentHeight = 0;
	bool isMaxHeight = false;
	bool maxHeightWas = false;

	cout << "Максимально возможная высота прыжка = " << MAX_HEIGHT << '\n';
	cout << "Введите высоту вашего прыжка: ";

	int maxHeight;
	cin >> maxHeight;
	double timeAtMaxHeight = sqrt(maxHeight * 2 / G);
	double initialSpeed = G * timeAtMaxHeight;
	cout << '\n';

	if (!IsValidHight(maxHeight))
	{
		cout << "Введите целое число от 0 до " << MAX_HEIGHT << '\n';
		return 1;
	}
	ProcessJump(timeAtMaxHeight, initialSpeed, currentHeight, isMaxHeight, maxHeightWas);
	return 0;
}