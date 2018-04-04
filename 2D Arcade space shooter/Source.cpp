//Main Includes
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>


//File Includes
#include "Entities.h"
#include "Player.h"
#include "GUI\button.hpp"



//Delete bools

	//Asteroid
	bool IsMarkedToDelete(const Asteroid & o)
	{
		return o.dead;
	}
	//Bullet
	bool IsMarkedToDelete2(const Bullet & i)
	{
		return i.dead;
	}
	//star
	bool IsMarkedToDelete3(const Star & s)
	{
		return s.dead;
	}



//Main function: First function to run.
	int main()
	{

		//File Refrences

		//Game Texture Sheet(s)
		sf::Texture TextureSheet;
		if (!TextureSheet.loadFromFile("Art/Texturesheet.png"))
			EXIT_FAILURE;


		//Game Font(s)
		sf::Font font1;
		if (!font1.loadFromFile("Big Pixel Light demo.otf"))
			EXIT_FAILURE;

		//Game Sound(s)
		// Load a music to play
		sf::Music shoot;
		if (!shoot.openFromFile("Sound/Laser_Shoot.wav"))
			return EXIT_FAILURE;

		sf::Music Explosion;
		if (!Explosion.openFromFile("Sound/Explosion.wav"))
			return EXIT_FAILURE;

		sf::Music hurt;
		if (!hurt.openFromFile("Sound/Hurt.wav"))
			return EXIT_FAILURE;




		//Create Window
		sf::RenderWindow Window(sf::VideoMode(500, 800), "D3RP", sf::Style::Close);

		//Frame Limit (higher frames can break the game)
		//Window.setFramerateLimit(60);

		//VSync
		Window.setVerticalSyncEnabled(1000);

		//Create all text Objects
		sf::Text DHPT("Hitpoints:", font1, 20);
		sf::Text scoreText("", font1, 20);
		sf::Text HitpointScore("", font1, 20);
		sf::Text GameOverText("Game Over", font1, 45);
		sf::Text RespawnAvailable("Press 'Space' to Restart", font1, 20);
		sf::Text MainMenuText1("Asteroid Shooter", font1, 35);
		sf::Text MainMenuText2("Press 'Space' to Start", font1, 20);

		//Set Variables for text Objects
		GameOverText.setPosition(60, 255);
		RespawnAvailable.setPosition(35, 320);

		scoreText.setPosition(0, 20);
		HitpointScore.setPosition(130, 0);

		MainMenuText1.setOrigin(sf::Vector2f(MainMenuText1.getGlobalBounds().width / 2, MainMenuText1.getGlobalBounds().height / 2));
		MainMenuText2.setOrigin(sf::Vector2f(MainMenuText2.getGlobalBounds().width / 2, MainMenuText2.getGlobalBounds().height / 2));

		MainMenuText1.setPosition(Window.getSize().x / 2, Window.getSize().y/2);
		MainMenuText2.setPosition(Window.getSize().x / 2, Window.getSize().y / 2 + 50);

		GameOverText.setOrigin(sf::Vector2f(GameOverText.getGlobalBounds().width / 2, GameOverText.getGlobalBounds().height / 2));
		RespawnAvailable.setOrigin(sf::Vector2f(RespawnAvailable.getGlobalBounds().width / 2, RespawnAvailable.getGlobalBounds().height / 2));

		GameOverText.setPosition(Window.getSize().x / 2, Window.getSize().y / 2);
		RespawnAvailable.setPosition(Window.getSize().x / 2, Window.getSize().y / 2 + 50);
		//Player

		Player player(TextureSheet, sf::Vector2f(100, 400), sf::Vector2i(20, 26), sf::Vector2i(64, 0));

		player.setHealth(5);
		player.setPos(sf::Vector2f(200, 500));

		//Player hitbox
		sf::RectangleShape playerHitbox;
		playerHitbox.setSize(sf::Vector2f(player.boundingBox().width - 20, player.boundingBox().height - 15));
		playerHitbox.setOrigin(sf::Vector2f(playerHitbox.getGlobalBounds().width / 2, playerHitbox.getGlobalBounds().height / 2));
		playerHitbox.setFillColor(sf::Color::White);

		//Vectors

			//Bullet Vector
			std::vector<Bullet> bulletVec;

			//Enemy Vector
			std::vector<Asteroid> asteroidVec;

			//Star Vecotr
			std::vector<Star> starVec;


		//Pointer to Event Handler
		sf::Event event;

		//Clocks
		sf::Clock BulletSpawnClock; // Timer before a new bullet can spawn
		sf::Clock AsteroidSpawnClock1; // Timer before a new asteroid can spawn
		sf::Clock AsteroidSpawnClock2; // Timer before a new asteroid can spawn
		sf::Clock StarSpawnClock1; // Timer before a new Star can spawn
		sf::Clock StarSpawnClock2; // Timer before a new Star can spawn
		sf::Clock StarSpawnClock3; // Timer before a new Star can spawn
		sf::Clock DelayClock1; // 
		sf::Clock DelayClock2; // Delay Asteroid Spawns at start
		sf::Clock DelayClock3; // Respawn Available delay
		sf::Clock DelayClock4; // Randomise star speed clock
		sf::Clock DelayClock5; // Delay Hit "Animation" stop
		sf::Clock ResetClock1; // Change between Draw player states.


		//Bools
		bool IsDead = false; // is the Player dead or not?
		bool Respawn = false; // Is player supposed to respawn?
		bool IsPaused = false; // Maybe the world is a computer simulation and it is paused?
		bool IsPlaying = false; // Is the player playing?
		bool IsFiring = true; // Of course he is firing. but only when he is playing.
		bool pHit = false; // Activate Flash Bool
		bool pFlash = false; // Flash player when hit by an enemy.
		//Integers
		int screenWidth;
		int screenHeight;
		int score;
		int Hitpoints;
		score = 0;
		Hitpoints = 5;
		screenWidth = Window.getSize().x;
		screenHeight = Window.getSize().y;

		//int speedRange;
		

		//Object initialization 
		Bullet newBullet(TextureSheet, sf::Vector2i(5, 10), sf::Vector2i(96, 0));
		Asteroid newAsteroid(TextureSheet, sf::Vector2i(22, 19), sf::Vector2i(32, 0));
		Star newStar(TextureSheet, sf::Vector2i(3, 3), sf::Vector2i(160, 0));
	


		//Window Loop
		while (Window.isOpen())
		{
			//Single Event Handling
			while (Window.pollEvent(event))
			{
				// check the type of the event...
				switch (event.type)
				{

					// window closed
				case sf::Event::Closed:
					Window.close();
					break;

				case sf::Event::KeyPressed:

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && IsPlaying == false)
					{
						IsPlaying = true;
						DelayClock2.restart();
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && IsDead == true)
					{
						Respawn = true;
						IsDead = false;
						DelayClock2.restart();
					}

					break;

				default:
					break;
				}
			}


			//Create Updateable Number Streams
			std::stringstream ScoreString;
			std::stringstream HPString;

			if (Hitpoints <= 0)
			{
				Hitpoints = 0;
			}

			//Handle player movement
			player.Movement(Window, event);

			//set the position of Playerhitbox to the position of the player
			playerHitbox.setPosition(sf::Vector2f(player.getPos().x + (player.boundingBox().width / 2), player.getPos().y + (player.boundingBox().height / 2)));




			if (DelayClock2.getElapsedTime().asSeconds() >= 0.5)
			{
				//Create asteroids on a timer
				if (AsteroidSpawnClock1.getElapsedTime().asSeconds() >= 0.87f)
				{

					


					if (IsPlaying == true) {
						int spawnRange = rand() % screenWidth + 20;
						float rotSpeed = rand() % -1 + 3;
						newAsteroid.setPos(sf::Vector2f(spawnRange, -20));
						newAsteroid.setSpeed(7);
						newAsteroid.setRotSpeed(rotSpeed);
						

						asteroidVec.push_back(newAsteroid);
					}


					AsteroidSpawnClock1.restart();
				}

				//Create asteroids on a timer
				if (AsteroidSpawnClock2.getElapsedTime().asSeconds() >= 0.65f)
				{
					if (IsPlaying == true) {
						int spawnRange = rand() % screenWidth + 20;
						newAsteroid.setPos(sf::Vector2f(spawnRange, -20));
						newAsteroid.setSpeed(6);
						newAsteroid.setRotSpeed(-1.51);

						asteroidVec.push_back(newAsteroid);
					}



					AsteroidSpawnClock2.restart();
				}

			}

				if (StarSpawnClock1.getElapsedTime().asSeconds() >= 0.51f)
				{
						int spawnRange = rand() % screenWidth + 20;
						newStar.setPos(sf::Vector2f(spawnRange, -20));

						
							int speed = 5;

							newStar.setSpeed(speed);

							float size = 1.25;

							newStar.setSize(size);

						starVec.push_back(newStar);
					StarSpawnClock1.restart();
				}
				if (StarSpawnClock2.getElapsedTime().asSeconds() >= 0.33f)
				{
						int spawnRange = rand() % screenWidth + 20;
						newStar.setPos(sf::Vector2f(spawnRange, -20));
						int speed = 4;

						newStar.setSpeed(speed);


						float size = 0.75;

						newStar.setSize(size);

						starVec.push_back(newStar);
					
					StarSpawnClock2.restart();
				}
				if (StarSpawnClock3.getElapsedTime().asSeconds() >= 0.42f)
				{
						int spawnRange = rand() % screenWidth + 20;
						newStar.setPos(sf::Vector2f(spawnRange, -20));
						int speed = 7;

						newStar.setSpeed(speed);

						float size = 1.75;

						newStar.setSize(size);

						starVec.push_back(newStar);
					StarSpawnClock3.restart();
				}

				

			//Access The individual Objects in BulletVec
		for (auto& StarOBJ : starVec)
		{

			StarOBJ.update(Window);

			//delete Stars that go beyond the screen.
			if (StarOBJ.getPos().y <= -screenHeight - 10)
			{
				StarOBJ.dead = true;
			}
		}

		//Access The individual Objects in BulletVec
		for (auto& BulletOBJ : bulletVec)
		{
			BulletOBJ.speed = 7 + player.moveSpd;
			//BulletOBJ.speed = 0;
			BulletOBJ.update();


			//delete bullets that go above the screen.
			if (BulletOBJ.getPos().y <= -20)
			{
				BulletOBJ.dead = true;
			}
		}

		//Access The individual Objects in AsteroidVec
		for (auto& AsteroidOBJ : asteroidVec)
		{
			
			
			AsteroidOBJ.update(Window);

			//delete asteroids that go beyond the screen while subtracting 100 points from your score.
			if (AsteroidOBJ.getPosY() >= screenHeight + 10)
			{
				AsteroidOBJ.dead = true;

				if (IsDead == false) {
					score = score - 100;

				}
			}

			std::cout << starVec.capacity();
				
			//Player / Asteroid Collision
			if (player.boundingBox().intersects(AsteroidOBJ.asteroidHitbox.getGlobalBounds()))
			{
				
				AsteroidOBJ.dead = true;
				hurt.play();
				if (pHit == false)
				{
					Hitpoints = Hitpoints - 1;
					pHit = true;
				}
				DelayClock5.restart();
			}

			//Bullet / Asteroid collision detection
			for (auto& BulletOBJ : bulletVec)
			{
				if (AsteroidOBJ.asteroidHitbox.getGlobalBounds().intersects(BulletOBJ.bulletHitbox.getGlobalBounds()))
				{
					Explosion.play();
					AsteroidOBJ.dead = true;
					BulletOBJ.dead = true;
					score = score + 100;

				}
			}
		}


		//Remove every bullet/Asteroid who's bool "dead" is true
		asteroidVec.erase(std::remove_if(asteroidVec.begin(), asteroidVec.end(), IsMarkedToDelete), asteroidVec.end());
		bulletVec.erase(std::remove_if(bulletVec.begin(), bulletVec.end(), IsMarkedToDelete2), bulletVec.end());
		starVec.erase(std::remove_if(starVec.begin(), starVec.end(), IsMarkedToDelete3), starVec.end());

		//Convert Score Integer to string
		ScoreString << score;
		scoreText.setString(ScoreString.str());

		//Convert HP Integer to string
		HPString << Hitpoints;
		HitpointScore.setString(HPString.str());

		//Flash "Animation"
		if (pHit == true)
		{
			IsFiring = false;
			if (ResetClock1.getElapsedTime().asSeconds() >= 0.01f && pFlash == false)
			{
				pFlash = true;
				ResetClock1.restart();
			}
			else 
			{
				pFlash = false;
				
			}
		}
		else
		{
			IsFiring = true;
		}

		if (DelayClock5.getElapsedTime().asSeconds() >= 0.7f && pHit == true)
		{
			pHit = false;
			pFlash = false;
		}

		//if Hitpoints is equal to ZERO, set bool "isDead" to true.
		if (Hitpoints == 0)
		{
			IsDead = true;
			DelayClock2.restart();
			

		}

		//Create Bullets on a timer
		if (IsFiring == true && IsDead == false && IsPaused == false && IsPlaying == true)
		{
			//Delay the firing at start.
			if (DelayClock2.getElapsedTime().asSeconds() >= 0.5)
			{
				//create a bullet every 0.15 seconds.
				if (BulletSpawnClock.getElapsedTime().asSeconds() >= 0.175f)
				{
					//check if player is dead before firing.
					if (IsDead == false) {
						newBullet.setPos(sf::Vector2f(player.player.getPosition().x + (player.boundingBox().width / 2), player.getPos().y));
						shoot.play();
						bulletVec.push_back(newBullet);
						BulletSpawnClock.restart();
					}

				}

			}
		}




		if (Respawn == true)
		{
			IsDead = false;
			player.setPos(sf::Vector2f(200, 500));
			Hitpoints = 5;
			score = 0;
			Respawn = false;
			DelayClock2.restart();
		}

		//Clear Window
		Window.clear();

		//Draw objects onto Window
		for (auto& StarOBJ : starVec)
		{
			StarOBJ.draw(Window);
		}
		for (auto& BulletOBJ : bulletVec)
		{
			BulletOBJ.draw(Window);
		}
		for (auto& AsteroidOBJ : asteroidVec)
		{
			AsteroidOBJ.draw(Window);
		}


		if (IsPlaying == true)
		{
			//Draw the Player
			if (IsDead == false) {
				if (pFlash == false)
				{
					Window.draw(player);
				}
			}
			Window.draw(DHPT);
			Window.draw(scoreText);
			Window.draw(HitpointScore);

		}

		if (IsPlaying == false)
		{
			Window.draw(MainMenuText1);
			Window.draw(MainMenuText2);
		}
		//Display Game Over text and Respawn Available text
		if (IsDead == true && IsPlaying == true)
		{
			Window.draw(GameOverText);
			
			if (DelayClock3.getElapsedTime().asSeconds() >= 0.5f) {

				Window.draw(RespawnAvailable);
				
			}
		}


		//Update Window
		Window.display();
	}

}
