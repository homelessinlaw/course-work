#pragma once
#include "map.h"
#include "Enitity.h"
#include "view.h"

class Enemy : public Enitity
{
public:
	enum {left,right,up,down} dir;
	Enemy(Image &image, float X, float Y, int W, int H, String Name) :Enitity(image, X, Y, W, H, Name){
	if (name == "EasyEnemy")
		{
			w = W; h = H;
			//image.createMaskFromColor(Color(41, 33, 59));
			x = X; y = Y;

			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;
		}
	}
	
	void interactionWithMap(float Dx, float Dy)
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (Dy > 0) { y = i * 32 - h;
					dy = 0;
					dx = 0.1;
					dir = right;
					}
					if (Dy < 0) { y = i * 32 + 32;
					dy = 0;
					dx = -0.1;
					dir = left;
					}
					if (Dx > 0) { x = j * 32 - w;
					dx = 0;
					dy = -0.1;
					dir = up;
//					sprite.scale(-1, 1);
					}
					if (Dx < 0) { x = j * 32 + 32; 
					dx = 0;
					dy = 0.1;
					dir = down;
					//sprite.scale(-1, 1);
					}

				}
				if (TileMap[i][j] == 's')
				{
					if (Dy > 0) { y = i * 32 - h; 
					dy = 0;
					dx = 0.1;
					dir = right;
					//sprite.scale(1, -1);
					}
					if (Dy < 0) { y = i * 32 + 32;
					dy = 0;
					dx = -0.1;
					dir = left;
					//sprite.scale(1, -1);
					}
					if (Dx > 0) {
						x = j * 32 - w; 
						//dx = -0.1;
						dx = 0;
						dy = -0.1;
						dir = up;
					}
					if (Dx < 0) { x = j * 32 + 32; dx = 0;
					dy = 0.1;
					dir = down;
					}

				}
			}
	}
	void update(float time,float CurrentFrame)
	{
		if (name == "EasyEnemy") {//для персонажа с таким именем логика будет такой

			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
			interactionWithMap(dx, dy);//обрабатываем столкновение по Х
			switch (dir)
			{
			case right:  sprite.setTextureRect(IntRect(64 * int(CurrentFrame) + 1, 195, 64, 58)); break;
			case left: sprite.setTextureRect(IntRect(64 * int(CurrentFrame) + 17, 67, 64, 58)); break;
			case down: sprite.setTextureRect(IntRect(64 * int(CurrentFrame) + 11, 128, 64, 61));; break;
			case up: sprite.setTextureRect(IntRect(64 * int(CurrentFrame) + 11, 0, 64, 58)); break;
			}
			x += dx * time;
			y += dy * time;
			sprite.setPosition(x , y ); //задаем позицию спрайта в место его центра
			if (health <= 0) { life = false; }
		}
	}
				};


