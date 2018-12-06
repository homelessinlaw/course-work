#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include "map.h"
#include "view.h"
#include "Player.h"
#include "Enemy.h"


using namespace sf;

int main()
{
	Image heroimage,fireim, Easyenemyim;
	heroimage.loadFromFile("images/golem-walk.png");
	Easyenemyim.loadFromFile("images/golem-walk.png");
	fireim.loadFromFile("images/fire.png");
	RenderWindow window(VideoMode(640, 480), "SFMLworks");
	view.reset(FloatRect(0, 0, 640, 480));
	float CurrentFrame = 0; // хранит текущ кадр
	Player p(heroimage, 250, 250, 64.0, 64.0,"hero");
	Enemy enemy(Easyenemyim, 850, 671, 64.0, 64.0, "EasyEnemy");
	animatedobj fire(fireim, 600, 300, 80.0, 80.0,"fire");
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);


	Font font; // это шрифт
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	//text.setColor(Color::Red);
	text.setStyle(Text::Bold | Text::Underlined);
	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); // дать прошедшее время в мили секундах
		clock.restart(); // время перезагружается
		time = time / 800; // скорость игры
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		/*if (p.life) {

			CurrentFrame1 += 0.01*time;
			if (CurrentFrame1 > 8) CurrentFrame1 -= 8;
			fire.sprite.setTextureRect(IntRect(100 * int(CurrentFrame1), 0, 100, 100));
		}*/
		/*else {
			view.rotate(0.01); clock.restart(); gameTimeClock.getElapsedTime().asSeconds();
			time /= 800;
		}*/
		//getplayercoordinatefromview(p.getplayercoordinateX(), p.getplayercoordinateY());
		if (CurrentFrame > 7) CurrentFrame -= 7;
		CurrentFrame += 0.005*time;
		p.update(time,CurrentFrame);
		enemy.update(time,CurrentFrame);
		fire.control(time, CurrentFrame);
		if (fire.getRect().intersects(p.getRect()))
		{
			p.tp(250, 250);
		}
		window.setView(view);
		window.clear();
		for (int i = 0; i < HEIGHT_map; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == 'f') s_map.setTextureRect(IntRect(96, 0, 32, 32));
				if (TileMap[i][j] == 'h') s_map.setTextureRect(IntRect(128, 0, 32, 32));
				if (TileMap[i][j] == 'x') s_map.setTextureRect(IntRect(32, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);

			}
		std::ostringstream playerHealth, gameTimeString;
		if (p.health < 0) p.health = 0;
		playerHealth << p.health; gameTimeString << gameTime;	
		text.setString("Здоровье:" + playerHealth.str() + "\nВремя игры:" + gameTimeString.str());
		text.setPosition(view.getCenter().x - 300, view.getCenter().y - 248);
		window.draw(text);
		window.draw(p.sprite);
		window.draw(enemy.sprite);
		window.draw(fire.sprite);
		window.display();
	}

	return 0;
}