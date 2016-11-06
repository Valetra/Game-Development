#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <string> 
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;
using namespace std;

using TypeOfDots = CircleShape;

struct Board
{
	string digit;
	double x;
	double y;
};

using TypeOfDigits = Board;
using DigitCircles = CircleShape;

struct MyClock
{
	TypeOfDots dot[60];
	TypeOfDigits digits[12];
	float x = 0;
	float y = 0;
	float angle = 0.0;
	Font font;
	Text text;
	CircleShape clockCircle;
	CircleShape centerCircle;
	Music clockTick;
	Texture clockImage;
	Texture clockBrand;
	Sprite clockBrandSprite;
	RectangleShape hourHand;
	RectangleShape minuteHand;
	RectangleShape secondsHand;
};

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const float CLOCK_CIRCLE_RADIUS = 250;
static const float CLOCK_CIRCLE_THICKNESS = 2;

void InitSettings(ContextSettings &settings)
{
	settings.antialiasingLevel = 8;
}

void InitWindowCenter(Vector2f &windowCenter, RenderWindow &window)
{
	windowCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
}

void SetHandsConfiguration(RectangleShape &hourHand, RectangleShape &minuteHand, RectangleShape &secondsHand, Vector2f &windowCenter)
{
	hourHand.setFillColor(Color::Black);
	minuteHand.setFillColor(Color::Black);
	secondsHand.setFillColor(Color::Red);

	hourHand.setOrigin(hourHand.getGlobalBounds().width / 2, hourHand.getGlobalBounds().height - 25);
	minuteHand.setOrigin(minuteHand.getGlobalBounds().width / 2, minuteHand.getGlobalBounds().height - 25);
	secondsHand.setOrigin(secondsHand.getGlobalBounds().width / 2, secondsHand.getGlobalBounds().height - 25);

	hourHand.setPosition(windowCenter);
	minuteHand.setPosition(windowCenter);
	secondsHand.setPosition(windowCenter);
}

void CreateClockScheme(RenderWindow &window, CircleShape &clockCircle, CircleShape &centerCircle, Vector2f &windowCenter)
{
	clockCircle.setPointCount(100);
	clockCircle.setOutlineThickness(CLOCK_CIRCLE_THICKNESS);
	clockCircle.setOutlineColor(Color::Black);
	clockCircle.setOrigin(clockCircle.getGlobalBounds().width / 2, clockCircle.getGlobalBounds().height / 2);
	clockCircle.setPosition(window.getSize().x / 2 + CLOCK_CIRCLE_THICKNESS, window.getSize().y / 2 + CLOCK_CIRCLE_THICKNESS);

	centerCircle.setPointCount(100);
	centerCircle.setFillColor(Color::Red);
	centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
	centerCircle.setPosition(windowCenter);
}

void PlayClockSound(Music &clockTick)
{
	if (!clockTick.openFromFile("resources/clock-1.wav"))
	{
		cout << "Sound wasn`t found\n";
	}
	else
	{
		clockTick.setLoop(true);
		clockTick.play();
	}
}

void CreateLogo(Texture &clockBrand)
{
	if (!clockBrand.loadFromFile("resources/sfml-logo.png"))
	{
		cout << "Logo not found\n";
	}
}

void CreateClockTexture(Sprite &clockBrandSprite, Texture &clockBrand, RenderWindow &window)
{
	clockBrandSprite.setTexture(clockBrand);
	clockBrandSprite.setOrigin(clockBrandSprite.getTextureRect().left + clockBrandSprite.getTextureRect().width / 2 - 30,
		clockBrandSprite.getTextureRect().top + clockBrandSprite.getTextureRect().height / 2 + 70);
	clockBrandSprite.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100.0f);
}

void CreateScheme(TypeOfDots *dot, TypeOfDigits *digits, RenderWindow &window, float angle, float x, float y)
{
	for (int i = 0; i < 12; i++)
	{
		digits[i].digit = to_string(i + 1);
	}

	int j = 2;
	for (int i = 0; i < 60; i++)
	{
		x = (CLOCK_CIRCLE_RADIUS - 10) * cos(angle);
		y = (CLOCK_CIRCLE_RADIUS - 10) * sin(angle);

		if (i % 5 == 0)
		{
			dot[i] = CircleShape(3);
			digits[j].x = ((CLOCK_CIRCLE_RADIUS - 50) * cos(angle)) - 6;
			digits[j].y = ((CLOCK_CIRCLE_RADIUS - 50) * sin(angle)) - 15;
			j++;
			if (j == 12)
			{
				j = 0;
			}
		}
		else
		{
			dot[i] = CircleShape(1);
		}
		dot[i].setFillColor(Color::Black);
		dot[i].setOrigin(dot[i].getGlobalBounds().width / 2, dot[i].getGlobalBounds().height / 2);
		dot[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);
		angle = angle + ((2.0f * M_PI) / 60.0f);
	}
}

void CreateClockBackground(Texture &clockImage, CircleShape &clockCircle)
{
	if (!clockImage.loadFromFile("resources/clock-brand.jpg"))
	{
		cout << "BackGround wasn`t found\n";
	}
	else
	{
		clockCircle.setTexture(&clockImage);
		clockCircle.setTextureRect(IntRect(40, 0, 500, 500));
	}
}

void ProcessEvent(Event &event, RenderWindow &window)
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
}

void SetDigitsOptions(Text &text, Font &font)
{
	if (!font.loadFromFile("resources/CyrilicOld.ttf"))
	{
		cout << "Fonts wasn`t load\n";
	}
	text.setFont(font);
	text.setColor(Color::Black);
	text.setCharacterSize(20);
	text.setStyle(Text::Bold);
}

void DrawObjects(MyClock &watch, RenderWindow &window, RectangleShape &hourHand, RectangleShape &minuteHand, RectangleShape &secondsHand, Sprite &clockBrandSprite)
{
	window.draw(watch.clockCircle);
	for (int i = 0; i < 60; i++)
	{
		window.draw(watch.dot[i]);
		if (i < 12)
		{
			watch.text.setPosition(watch.digits[i].x + window.getSize().x / 2, watch.digits[i].y + window.getSize().y / 2);
			watch.text.setString(watch.digits[i].digit);
			window.draw(watch.text);
		}
	}
	window.draw(clockBrandSprite);
	window.draw(hourHand);
	window.draw(minuteHand);
	window.draw(secondsHand);
	window.draw(watch.centerCircle);
}

void SetHandsOfTime(RectangleShape &hourHand, RectangleShape &minuteHand, RectangleShape &secondsHand)
{
	time_t currentTime = time(NULL);
	struct tm * ptm = localtime(&currentTime);

	hourHand.setRotation(ptm->tm_hour * 30 + (ptm->tm_min / 2));
	minuteHand.setRotation(ptm->tm_min * 6 + (ptm->tm_sec / 12));
	secondsHand.setRotation(ptm->tm_sec * 6);
}

void ClockWork(MyClock &watch, RenderWindow &window)
{
	while (window.isOpen())
	{
		Event event;
		ProcessEvent(event, window);
		window.clear(Color::White);
		SetHandsOfTime(watch.hourHand, watch.minuteHand, watch.secondsHand);
		DrawObjects(watch, window, watch.hourHand, watch.minuteHand, watch.secondsHand, watch.clockBrandSprite);
		window.display();
	}
}

void InitSizeOfHands(MyClock &watch)
{
	watch.hourHand.setSize(Vector2f(5, 180));
	watch.minuteHand.setSize(Vector2f(3, 240));
	watch.secondsHand.setSize(Vector2f(2, 250));
}

void InitClock(MyClock &watch, RenderWindow &window, Vector2f &windowCenter)
{
	InitSizeOfHands(watch);
	watch.clockCircle.setRadius(CLOCK_CIRCLE_RADIUS);
	watch.centerCircle.setRadius(10);
	SetDigitsOptions(watch.text, watch.font);
	CreateScheme(watch.dot, watch.digits, window, watch.angle, watch.x, watch.y);
	CreateClockScheme(window, watch.clockCircle, watch.centerCircle, windowCenter);
	SetHandsConfiguration(watch.hourHand, watch.minuteHand, watch.secondsHand, windowCenter);
	PlayClockSound(watch.clockTick);
	CreateLogo(watch.clockBrand);
	CreateClockTexture(watch.clockBrandSprite, watch.clockBrand, window);
	CreateClockBackground(watch.clockImage, watch.clockCircle);
}

int main()
{
	ContextSettings settings;
	InitSettings(settings);
	Vector2f windowCenter;
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Analog Clock", Style::Close, settings);

	InitWindowCenter(windowCenter, window);

	MyClock watch;

	InitClock(watch, window, windowCenter);
	ClockWork(watch, window);

	return EXIT_SUCCESS;
}