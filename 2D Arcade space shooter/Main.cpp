#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Asteroid.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include "GUI\button.hpp"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <algorithm>
#include <string>
#include <cctype>


int main()
{

		sf::Texture playertexture;
	if (!playertexture.loadFromFile("Art/Images_06.png"))
		EXIT_FAILURE;

	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("Art/Images_08.png"))
		EXIT_FAILURE;

	sf::Texture asteroidTexture;
	if (!asteroidTexture.loadFromFile("Art/Images_01.png"))
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
	std::vector<Asteroid> asteroidVec;

/*	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(2, 2));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);	*/
	

	player.setHealth(4);
	player.setPos(sf::Vector2f(200,500));

	sf::Clock clock;
	sf::Clock clock2;
	sf::Clock clock3;

	sf::Time timeElapsed = clock.getElapsedTime();
	sf::Time timeElapsed2 = clock.getElapsedTime();

	float lastTime = 0;

	float playerSpd = player.moveSpd;
	
	bool isFiring = false;
	bool isPlaying = true;

	sf::Vector2f pos = player.getPos();
	int posx = rand() % 400 + 0;

	Bullet newBullet(bulletTexture, sf::Vector2f(5, 10), sf::Vector2i(0, 0));
	Asteroid newAsteroid(asteroidTexture, sf::Vector2f(32, 32), sf::Vector2i(0, 0));

	newAsteroid.setHP(4);

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

		



		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
		//	gameView.move(-400, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
		//	gameView.move(400, 0);
		}
		*/
		
			
		


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			

			
		}

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			isFiring = true;
		}
		else
		{
			isFiring = false;
		}
		
		window.clear();

	/*	float currentTime = clock.restart().asSeconds();
		float fps = 1.f / (currentTime - lastTime);
		lastTime = currentTime;

		std::cout << lastTime << " \a";
*/
		if (isFiring == true)
		{
			if (clock.getElapsedTime().asSeconds() >= 0.15f)
			{
			
			newBullet.setPos(sf::Vector2f(player.getPos().x + (player.getRight() - (newBullet.getCenterX())), player.getPos().y));
			bulletVec.push_back(newBullet);
			

		
			clock.restart();
			}
			
		}
		
		

		if (clock2.getElapsedTime().asSeconds() >= 1.5f)
		{
			int spawnRange = rand() % 380 + 20;
			newAsteroid.setPos(sf::Vector2f(spawnRange, -20));
			newAsteroid.setHP(3);
			asteroidVec.push_back(newAsteroid);
			

			

			clock2.restart();
		}

		





		
		for (auto& bulletObj : bulletVec) {

			bulletObj.draw(window);
			bulletObj.fire(playerSpd + 10);

			}

		for (auto& asteroidObj : asteroidVec) {

			asteroidObj.draw(window);
			asteroidObj.movement(-5);
			if (asteroidObj.boundingBox().intersects(newBullet.boundingBox()))
			{
				asteroidObj.setHP(asteroidObj.hitpoints - 1);
			}

		}

		int astHitpoints = newAsteroid.hitpoints;

		asteroidVec.erase(std::remove_if(asteroidVec.begin(), asteroidVec.end(),newAsteroid.hitpoints));

/*
		if (clock3.getElapsedTime().asSeconds() > 1.2f) {
			auto it = std::find(bulletVec.begin(), bulletVec.end(), newBullet);

			if (it != bulletVec.end()) {
				using std::swap;

				// swap the one to be removed with the last element
				// and remove the item at the end of the container
				// to prevent moving all items after '5' by one
				swap(*it, bulletVec.back());
				bulletVec.pop_back();
			}
		}
		*/
		/*if (newBullet.boundingBox().intersects(newAsteroid.boundingBox()))
		{
			newAsteroid.setHP(newAsteroid.hitpoints - 1);
			bulletVec.pop_back();
		}
			*/
		player.Movement(window, event);



			//std::cout << bulletVec.size() << std::endl;
			//std::cout << "X: " << player.getPos().x << "  Y: " << player.getPos().y << "\n";
		
			

		window.draw(player);

	//	window.draw(rectangle);

		window.display();
	}

	return 0;
}

