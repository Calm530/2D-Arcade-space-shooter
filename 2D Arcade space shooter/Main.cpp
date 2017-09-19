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

	sf::Time timeElapsed = clock.getElapsedTime();
	sf::Time timeElapsed2 = clock.getElapsedTime();

	float lastTime = 0;

	float playerSpd = player.moveSpd;
	
	bool isFiring = false;
	bool isPlaying = true;
	bool isDead = false;

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



		if (isFiring == true)
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
			int spawnRange = rand() % 380 + 20;
			newAsteroid.setPos(sf::Vector2f(spawnRange, -20));
			newAsteroid.setHP(3);
			asteroidVec.push_back(newAsteroid);




			clock2.restart();
		}
		if (clock4.getElapsedTime().asSeconds() >= 0.7f)
		{
			int spawnRange = rand() % 380 + 20;
			newAsteroid.setPos(sf::Vector2f(spawnRange, -20));
			newAsteroid.setHP(3);
			asteroidVec.push_back(newAsteroid);




			clock4.restart();
		}



		window.clear();

		sf::FloatRect bulletBox;
		sf::FloatRect AsteroidBox;
		sf::FloatRect playerBox;


		playerBox = player.boundingBox();



		for (auto& bulletObj : bulletVec)
		{

			bulletObj.draw(window);
			bulletObj.fire(playerSpd + 10);
			bulletBox = bulletObj.boundingBox();

			if (bulletBox.intersects(AsteroidBox))
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
					score = score + 50;
					asteroidObj.dead = true;
				}
				if (asteroidObj.getPosY() >= 610)
				{
					if (isDead == false) {
						score = score - 100;
					}
					asteroidObj.dead = true;
				}


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

			window.draw(DHPT);
			window.draw(HitpointScore);
			window.draw(scoreText);

			//	window.draw(rectangle);

			window.display();
		}
	

	return 0;
}



template <class ForwardIterator, class UnaryPredicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last,
	UnaryPredicate pred)
{
	ForwardIterator result = first;
	while (first != last) {
		if (!pred(*first)) {
			*result = *first;
			++result;
		}
		++first;
	}
	return result;
}