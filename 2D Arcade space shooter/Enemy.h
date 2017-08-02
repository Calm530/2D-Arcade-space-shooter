#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

class Enemy 
{
public:
	Enemy(sf::Vector2f);
	~Enemy();

	void setPos(sf::Vector2f);
	void move(int);

	bool checkColl(Bullet);

	void draw(sf::RenderWindow& window)
	{
		window.draw(enemy);
	}

	int getSizeX() {
		return enemy.getSize().x;
	}
	int getSizeY() {
		return enemy.getSize().y;
	}

private:
	sf::RectangleShape enemy;



};

Enemy::Enemy(sf::Vector2f size)
{
	enemy.setSize(size);
	enemy.setOutlineColor(sf::Color::Red);
	enemy.setOutlineThickness(2);

}

Enemy::~Enemy()
{
}
void Enemy::setPos(sf::Vector2f newPos)
{
	enemy.setPosition(newPos);
}
bool Enemy::checkColl(Bullet bullet)
{
	if (bullet.getRight() > enemy.getPosition().x &&
		bullet.getTop() < enemy.getPosition().y + enemy.getSize().y &&
		bullet.getBottom() > enemy.getPosition().y)
	{
		return true;
		std::cout << "enemy hit";
	}
	else
	{
		return false;
	}


}
void Enemy::move(int speed)
{

	enemy.move(0, speed);

}