#pragma once

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



class Game : public sf::Transformable
{
public:


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



	sf::Event event;


	Player player(playertexture, sf::Vector2f(100, 400), sf::Vector2f(20, 26), sf::Vector2i(0, 0));

	std::vector<Bullet> bulletVec;
	std::vector<Asteroid> asteroidVec;

	if (player.Health <= 0)
	{
		player.setHealth(0);
	}

	sf::Text DHPT(hitpointText, font1, 20);
	sf::Text scoreText("", font1, 20);
	sf::Text HitpointScore("", font1, 20);
	sf::Text GameOverText("Game Over", font1, 45);
	sf::Text RespawnAvailable("Press 'Space' to Restart", font1, 20);
	sf::Text MainMenuText1("Asteroid Shooter", font1, 35);
	sf::Text MainMenuText2("Press 'Space' to Start", font1, 20);

	GameOverText.setPosition(60, 255);
	RespawnAvailable.setPosition(35, 320);
	MainMenuText1.setPosition(20, 235);
	MainMenuText2.setPosition(45, 280);

	scoreText.setPosition(sf::Vector2f(0, 20));
	HitpointScore.setPosition(sf::Vector2f(130, 0));

	int score = 0;
	int HPscore = 0;

	player.setHealth(5);
	player.setPos(sf::Vector2f(200, 500));

	sf::RectangleShape playerHitbox;
	playerHitbox.setSize(sf::Vector2f(player.boundingBox().width - 20, player.boundingBox().height - 15));
	playerHitbox.setOrigin(sf::Vector2f(playerHitbox.getGlobalBounds().width / 2, playerHitbox.getGlobalBounds().height / 2));
	playerHitbox.setFillColor(sf::Color::White);



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


	struct bullet() {
		sf::Sprite bullet;
	};

	void Update();

}