#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

class Asteroid
{
public:
	Asteroid();
	Asteroid(sf::Texture& TEMP_Texture, sf::Vector2f size, sf::Vector2i sourcepos);
	~Asteroid();



	int getRight() {
		return asteroid.getTexture()->getSize().x * (0.5f * asteroid.getScale().x);
	}
	int getLeft() {
		return asteroid.getTexture()->getSize().x;
	}
	int getTop() {
		return asteroid.getTexture()->getSize().y;
	}
	int getBottom() {
		return asteroid.getTexture()->getSize().y * (0.5f * asteroid.getScale().y);
	}

	int getCenterX() {
		return (asteroid.getTexture()->getSize().x * (0.5f * asteroid.getScale().x)) / 2;
	}

	sf::FloatRect boundingBox() { return asteroid.getGlobalBounds(); }

	void movement(int);

	float hitpoints;

	void setHP(float);

	void setPos(sf::Vector2f);


	sf::Vector2f getPos() {
		return asteroid.getPosition();
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(asteroid);
	}

private:

	int rSourceY;
	int rSourceX;
	int rSourceWidht;
	int rSourceHeight;

	sf::Sprite asteroid;
	sf::Sprite getSprite() const;

};

Asteroid::Asteroid()
{

}
Asteroid::Asteroid(sf::Texture& TEMP_Texture, sf::Vector2f size, sf::Vector2i sourcepos)
{


	asteroid.setTexture(TEMP_Texture);
	asteroid.setOrigin(asteroid.getTexture()->getSize().x * (0.5f * asteroid.getScale().x), asteroid.getTexture()->getSize().y * (0.5f * asteroid.getScale().y));
	asteroid.setScale(2.0f, 2.0f);

	rSourceY = sourcepos.y;
	rSourceX = sourcepos.x;
	rSourceWidht = size.x;
	rSourceHeight = size.y;

	//bullet.setTextureRect(sf::IntRect(rSourceX, rSourceY, rSourceWidht, rSourceHeight));
}
Asteroid::~Asteroid()
{

}
void Asteroid::movement(int speed)
{

	asteroid.move(0, -speed);

}

sf::Sprite Asteroid::getSprite() const
{
	return asteroid;
}

void Asteroid::setHP(float hp)
{
	hitpoints = hp;
}

void Asteroid::setPos(sf::Vector2f newPos)
{
	asteroid.setPosition(newPos);
}

