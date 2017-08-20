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

	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("Art/Images_08.png"))
		EXIT_FAILURE;

	sf::RenderWindow window(sf::VideoMode(400, 600), "D3RP", sf::Style::Close);
	
	window.setFramerateLimit(60);
	sf::Event event;
	
/*	sf::View gameView;
	gameView.setSize(400, 600);
	gameView.setCenter(0, 0);
*/	


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

		while (window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		sf::Vector2f playerOrigin = player.origin();

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
		//	gameView.move(-400, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
		//	gameView.move(400, 0);
		}
		
		
			
		
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			std::cout << player.getPos().x + playerOrigin.x;
		}

		player.Movement(window,event);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
			if (clock.getElapsedTime().asSeconds() >= 0.15f)
			{

			Bullet newBullet(bulletTexture, sf::Vector2f(5,10),sf::Vector2i(0,0));
			newBullet.setPos(sf::Vector2f(player.getPos().x + (player.getRight() - (newBullet.getRight() / 2)), player.getPos().y));
			bulletVec.push_back(newBullet);
		
			clock.restart();
			}
			
		}
				



		for (auto& bulletObj : bulletVec) {

			bulletObj.draw(window);
			bulletObj.fire(playerSpd + 10);

			}


			




			//std::cout << bulletVec.size() << std::endl;
			//std::cout << "X: " << player.getPos().x << "  Y: " << player.getPos().y << "\n";
		
			

		window.draw(player);

		window.draw(rectangle);

		window.display();
	}

	return 0;
}

