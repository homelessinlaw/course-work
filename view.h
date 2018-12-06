#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


View view;

void getplayercoordinatefromview(float x, float y)
{
	float tempX = x; float tempY = y;

	if (x < 320) tempX = 320;
	if (y < 240) tempY = 240;
	if (y > 554) tempY = 554;
	if (x > 1600) tempX = 1600;
	view.setCenter(tempX, tempY);
}
