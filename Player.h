#pragma once
#include "map.h"
#include "view.h"
#include "Enitity.h"
class Player : public Enitity
{
private:
	float x, y, damage;
public:
	 // координаты, высота ширина ускорение скорость 
	enum { left, right, up, down, idle } dir;// направление

	Player(Image &image, float X, float Y, int W, int H, String Name) :Enitity(image, X, Y, W, H, Name)
	{
		dx = 0; dy = 0; speed = 0; health = 100;
		life = true;
		w = W; h = H;
		//image.createMaskFromColor(Color(41, 33, 59));
		x = X; y = Y;
	sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void control(float time,float CurrentFrame)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			dir = left; speed = 0.1;
			sprite.setTextureRect(IntRect(64 * int(CurrentFrame)+17, 67, 64, 58));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			dir = right; speed = 0.1;
			sprite.setTextureRect(IntRect(64 * int(CurrentFrame)+1, 195, 64, 58));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			dir = up; speed = 0.1;
			sprite.setTextureRect(IntRect(64 * int(CurrentFrame)+11, 0, 64, 58));

		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			dir = down; speed = 0.1;
			sprite.setTextureRect(IntRect(64 * int(CurrentFrame)+11, 128, 64, 61));

		}

	}
	void tp(float X, float Y)
	{
		x = X;
		y = Y;
	}
	void update(float time, float CurrentFrame)
	{
		control(time,CurrentFrame);
		switch (dir)
		{
		case right: dx = speed; dy = 0; break;
		case left: dx = -speed; dy = 0; break;
		case down: dx = 0; dy = speed; break;
		case up: dx = 0; dy = -speed; break;
		}
		x += dx * time;
		y += dy * time;
		speed = 0;
		sprite.setPosition(x, y);
		interactionWithMap();
		if (health <= 0) { life = false; speed = 0; }
		if(life) getplayercoordinatefromview(x, y);
	}
	float getplayercoordinateX()
	{
		return x;
	}
	float getplayercoordinateY()
	{
		return y;
	}
	void interactionWithMap()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (dy > 0)
						y = i * 32 - h;
					if (dy < 0)
						y = i * 32 + 32;
					if (dx > 0)
						x = j * 32 - w;
					if (dx < 0)
						x = j * 32 + 32;
				}
				if (TileMap[i][j] == 's')
				{
					
					if (dy > 0)
						y = i * 32 - h;
					if (dy < 0)
						y = i * 32 + 32;
					if (dx > 0)
						x = j * 32 - w;
					if (dx < 0)
						x = j * 32 + 32;

				}
				if (TileMap[i][j] == 'f')
				{
					health -= 50;
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'h')
				{
					health += 20;
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'x')
				{
					x = 250;
					y = 250;
				}
			}
	}
};

class animatedobj : public Enitity
{public:
	animatedobj(Image &image, float X, float Y, int W, int H, String Name) :Enitity(image, X, Y, W, H, Name)
	{ 
		life = true;
		w = W; h = H;
		//image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void control(float time, float CurrentFrame)
	{
		sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 0, 100, 100));
		sprite.setPosition(x, y);
	 }
private:
	float x;
	float y;
};
