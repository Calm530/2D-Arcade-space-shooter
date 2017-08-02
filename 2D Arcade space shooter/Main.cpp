#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include "GUI\button.hpp"

int main()
{

		sf::Texture playertexture;
	if (!playertexture.loadFromFile("Art/Images_06.png"))
		EXIT_FAILURE;

	sf::RenderWindow window(sf::VideoMode(400, 600), "D3RP", sf::Style::Close);
	
	window.setFramerateLimit(60);

	


	Player player(playertexture, sf::Vector2f(100, 400), sf::Vector2f(20, 26), sf::Vector2i(0, 0));
	std::vector<Bullet> bulletVec;
	std::vector<Enemy> enemyVec;

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(2, 2));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	

	player.setHealth(4);
	player.setPos(sf::Vector2f(200,500));

	sf::Clock clock;

	float playerSpd = player.moveSpd;
	
	bool isFiring = false;
	bool isPlaying = true;

	sf::Vector2f pos = player.getPos();
	int posx = rand() % 400 + 0;

	while (window.isOpen())
	{

		
		sf::Vector2f playerOrigin = player.origin();

		
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			std::cout << player.getPos().x + playerOrigin.x;
		}

		player.Movement(window,event);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isFiring = true;
		}
		else
		{
			isFiring = false;
		}

		window.clear();


		if (isFiring == true)
		{
			if (clock.getElapsedTime().asSeconds() >= 0.18f)
			{

			Bullet newBullet(sf::Vector2f(8, 50));
			newBullet.setPos(sf::Vector2f(player.getPos().x + (player.getRight() - (newBullet.getRight() / 2)), player.getPos().y));
			bulletVec.push_back(newBullet);
		
			clock.restart();
			}
			
		}
				



			for (int i = 0; i < bulletVec.size(); i++) {

				bulletVec[i].draw(window);
				bulletVec[i].fire(playerSpd + 20);

			}



			for (int i = 0; i < enemyVec.size(); i++) {


				enemyVec[i].draw(window);
				enemyVec[i].move(5);
			}


			//std::cout << bulletVec.size() << std::endl;
			//std::cout << "X: " << player.getPos().x << "  Y: " << player.getPos().y << "\n";
		
			

		window.draw(player);

		window.draw(rectangle);

		window.display();
	}

	return 0;
}

