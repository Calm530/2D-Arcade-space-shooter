#include "Game.h"

Game::Update() {


	player.Movement(window, event);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isPlaying == false)
	{
		isPlaying = true;
	}

	playerHitbox.setPosition(sf::Vector2f(player.getPos().x + (player.boundingBox().width / 2), player.getPos().y + (player.boundingBox().height / 2)));

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

		if (clock6.getElapsedTime().asSeconds() >= 2.5f && isDead == true) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{

				respawn = true;
				clock6.restart();
			}
		}

		if (clock7.getElapsedTime().asSeconds() >= 0.5)
		{
			if (clock.getElapsedTime().asSeconds() >= 0.15f)
			{
				if (isDead == false) {
					newBullet.setPos(player.getPos());
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


		playerBox = playerHitbox.getGlobalBounds();



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
			if (bulletObj.getPos().y <= -10)
			{
				bulletObj.dead = true;
			}
		}

		for (auto& asteroidObj : asteroidVec)
		{

			asteroidObj.draw(window);
			asteroidObj.movement(-7);
			asteroidObj.update();



			AsteroidBox = asteroidObj.asteroidHitbox.getGlobalBounds();
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


		asteroidVec.erase(std::remove_if(asteroidVec.begin(), asteroidVec.end(), IsMarkedToDelete), asteroidVec.end());
		bulletVec.erase(std::remove_if(bulletVec.begin(), bulletVec.end(), IsMarkedToDelete2), bulletVec.end());



		if (isDead == false) {
			window.draw(player);
			//window.draw(playerHitbox);

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