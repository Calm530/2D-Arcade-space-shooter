#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

class Asteroid : public sf::Transformable
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
	void update();
		
	bool dead = false;

	void setPos(sf::Vector2f);


	sf::Vector2f getPos() {
		return asteroid.getPosition();
	}
	float getPosY() {
		return asteroid.getPosition().y;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(asteroid);
	}

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
	asteroid.setScale(2.3f, 2.3f);
	hitpoints = 1;

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

void Asteroid::update()
{
	if (hitpoints <= 0)
	{
		dead = true;
	}

}

void Asteroid::setPos(sf::Vector2f newPos)
{
	asteroid.setPosition(newPos);
}


