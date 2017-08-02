#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet();
	Bullet(sf::Vector2f);
	~Bullet();

	void fire(int);

	int getRight() {
		return bullet.getPosition().x + bullet.getSize().x;
	}
	int getLeft() {
		return bullet.getPosition().x;
	}
	int getTop() {
		return bullet.getPosition().y;
	}
	int getBottom() {
		return bullet.getPosition().y + bullet.getSize().y;
	}

	sf::FloatRect size() { return bullet.getGlobalBounds(); }

	void setPos(sf::Vector2f);
	

	sf::Vector2f getPos() {
		return bullet.getPosition();
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(bullet);
	}

private:



	sf::RectangleShape bullet;

};

Bullet::Bullet()
{

}
Bullet::Bullet(sf::Vector2f size)
{
	bullet.setOrigin(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2);
	bullet.setSize(size);

}
Bullet::~Bullet()
{

}

void Bullet::fire(int speed)
{

	bullet.move(0, -speed);

}

void Bullet::setPos(sf::Vector2f newPos)
{
	bullet.setPosition(newPos);
}

