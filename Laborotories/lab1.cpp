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

	// ����� ����������� ��������� ������ ������
	cout << "����������� ��������� ������ ������ = " << MAX_HEIGHT << '\n';
	cout << "������� ������ ������ ������: ";
	cin >> maxHeight;
	printf("\n");
	double timeAtMaxHeight = sqrt(maxHeight * 2 / G);
	double initialSpeed = G * timeAtMaxHeight;
	if (!isValidHight(maxHeight))
	{
		cout << "������� ����� ����� �� 0 �� " << MAX_HEIGHT << '\n';
		return 1;
	}

	for (double currentTime = 0; currentTime < timeAtMaxHeight * 2; currentTime += 0.1f)
	{
		if (!isMaxHeight && currentTime > timeAtMaxHeight)
		{
			isMaxHeight = true;
			currentHeight = initialSpeed * timeAtMaxHeight - 0.5f * G * pow(timeAtMaxHeight, 2);
			cout << "����� ��������������� ������������ ������ =" << timeAtMaxHeight << " ������� ������ = " << currentHeight << '\n';
		}
		currentHeight = initialSpeed * currentTime - 0.5f * G * pow(currentTime, 2);
		cout << "������� ����� = " << currentTime << " ������� ������ = " << currentHeight << '\n';
	}

	currentHeight = initialSpeed * (timeAtMaxHeight * 2) - 0.5f * G * pow(timeAtMaxHeight * 2, 2);
	cout << "����� ��������������� ������������ ������ =" << timeAtMaxHeight * 2 << "\n������� ������ = " << currentHeight << '\n';
	return 0;
}