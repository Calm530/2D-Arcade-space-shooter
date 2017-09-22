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
#include <sstream>

bool IsMarkedToDelete(const Asteroid & o)
{
	return o.dead;
}
bool IsMarkedToDelete2(const Bullet & i)
{
	return i.dead;
}



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

	sf::Font font1;
	if (!font1.loadFromFile("Big Pixel Light demo.otf"))
		EXIT_FAILURE;

	std::string hitpointText("Hitpoints:");

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

	if (player.Health <= 0)
	{
		player.setHealth(0);
	}

	sf::Text DHPT(hitpointText,font1,20);
	sf::Text scoreText("", font1, 20);
	sf::Text HitpointScore("", font1, 20);
	sf::Text GameOverText("Game Over", font1, 45);
	sf::Text RespawnAvailable("Press 'Space' to Restart", font1, 20);
	sf::Text MainMenuText1("Asteroid Shooter", font1, 35);
	sf::Text MainMenuText2("Press 'Space' to Start", font1, 20);

	GameOverText.setPosition(45, 255);
	RespawnAvailable.setPosition(35, 320);
	MainMenuText1.setPosition(20, 235);
	MainMenuText2.setPosition(45, 280);

	scoreText.setPosition(sf::Vector2f(0,20));
	HitpointScore.setPosition(sf::Vector2f(130, 0));

	int score = 0;
	int HPscore = 0;

	player.setHealth(5);
	player.setPos(sf::Vector2f(200,500));

	sf::Clock clock;
	sf::Clock clock2;
	sf::Clock clock3;
	sf::Clock clock4;
	sf::Clock clock5;
	sf::Clock clock6;
	sf::Clock clock7;

	sf::Time timeElapsed = clock.getElapsedTime();
	sf::Time timeElapsed2 = clock.getElapsedTime();

	float lastTime = 0;

	float playerSpd = player.moveSpd;
	
	bool isFiring = false;
	bool isPlaying = false;
	bool isDead = false;
	bool respawn = false;
	bool isPaused = false;

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isPlaying == false)
		{
			isPlaying = true;
		}


		window.clear();

		if (isPlaying == true)
		{



			std::stringstream ss;
			std::stringstream PHS;

			sf::Vector2f playerOrigin = player.origin();



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			{

				std::cout << asteroidVec.size();

			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				isFiring = true;
			}
			else
			{
				isFiring = false;
			}


			if (clock6.getElapsedTime().asSeconds() >= 2.5f && isDead == true) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{

					respawn = true;
					clock6.restart();
				}
			}

			if (isFiring == true && clock7.getElapsedTime().asSeconds() >= 0.5)
			{
				if (clock.getElapsedTime().asSeconds() >= 0.15f)
				{
					if (isDead == false) {
						newBullet.setPos(sf::Vector2f(player.getPos().x + (player.getRight() - (newBullet.getCenterX())), player.getPos().y));
						bulletVec.push_back(newBullet);
					}


					clock.restart();
				}

			}



			if (clock2.getElapsedTime().asSeconds() >= 1.3f)
			{
				if (isPlaying == true) {
					int spawnRange = rand() % 380 + 20;
					newAsteroid.setPos(sf::Vector2f(spawnRange, -20));
					newAsteroid.setHP(3);
					asteroidVec.push_back(newAsteroid);
				}



				clock2.restart();
			}
			if (clock4.getElapsedTime().asSeconds() >= 0.7f)
			{
				if (isPlaying == true) {
					int spawnRange = rand() % 380 + 20;

					newAsteroid.setPos(sf::Vector2f(spawnRange, -20));
					newAsteroid.setHP(3);
					asteroidVec.push_back(newAsteroid);
				}
				




				clock4.restart();
			}



			

			sf::FloatRect bulletBox;
			sf::FloatRect AsteroidBox;
			sf::FloatRect playerBox;


			playerBox = player.boundingBox();



			for (auto& bulletObj : bulletVec)
			{

				bulletObj.draw(window);
				bulletObj.fire(playerSpd + 10);
				bulletObj.update();
				bulletBox = bulletObj.boundingBox();

				if (bulletBox.intersects(AsteroidBox))
				{
					bulletObj.dead = true;
				}
				if (bulletObj.getPos().y >= 610)
				{
					bulletObj.dead = true;
				}

			}




			for (auto& asteroidObj : asteroidVec)
			{

				asteroidObj.draw(window);
				asteroidObj.movement(-7);
				asteroidObj.update();
				AsteroidBox = asteroidObj.boundingBox();


				if (AsteroidBox.intersects(bulletBox))
				{
					asteroidObj.dead = true;
					score = score + 100;
				}

				if (AsteroidBox.intersects(playerBox))
				{

					player.setHealth(player.Health - 1);
					if (isDead == false) {
						
						asteroidObj.dead = true;
					}

				}

				if (asteroidObj.getPosY() >= 610)
				{
					if (isDead == false) {
						score = score - 100;
					}
					asteroidObj.dead = true;
				}
				if (asteroidObj.getPosY() >= -30 && respawn == true)
				{

					asteroidObj.dead = true;
				}
			}

			HPscore = player.Health;

			ss << score;
			scoreText.setString(ss.str());
			PHS << HPscore;

			if (isDead == false)
			{
				HitpointScore.setString(PHS.str());

			}




			if (player.Health == 0)
			{
				isDead = true;

			}
			/*for (auto& asteroidObj : asteroidVec)
			{

			asteroidObj.draw(window);
			asteroidObj.movement(-5);
			asteroidObj.update();
			AsteroidBox = asteroidObj.boundingBox();


			if (AsteroidBox.intersects(bulletBox))
			{
			asteroidObj.dead = true;
			}

			}*/



			asteroidVec.erase(std::remove_if(asteroidVec.begin(), asteroidVec.end(), IsMarkedToDelete), asteroidVec.end());
			bulletVec.erase(std::remove_if(bulletVec.begin(), bulletVec.end(), IsMarkedToDelete2), bulletVec.end());

			player.Movement(window, event);



			//std::cout << bulletVec.size() << std::endl;
			//std::cout << "X: " << player.getPos().x << "  Y: " << player.getPos().y << "\n";


			if (isDead == false) {
				window.draw(player);
			}




			if (isDead == true) {
				window.draw(GameOverText);
			}
			window.draw(DHPT);
			window.draw(HitpointScore);
			window.draw(scoreText);

			if (clock6.getElapsedTime().asSeconds() >= 2.5f && isDead == true)
			{
				window.draw(RespawnAvailable);

			}

			if (respawn == true)
			{
				isDead = false;
				player.setPos(sf::Vector2f(200, 500));
				player.setHealth(5);
				score = 0;
				respawn = false;
				clock7.restart();
			}

			//	window.draw(rectangle);

		}
		if (isPlaying == false)
		{
			window.draw(MainMenuText2);
			window.draw(MainMenuText1);
			clock7.restart();
		}


		if (isDead == false)
		{
			clock6.restart();
		}


			window.display();


		}
	

	return 0;
}



