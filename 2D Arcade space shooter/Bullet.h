#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet();
	Bullet(sf::Texture& TEMP_Texture, sf::Vector2f size, sf::Vector2i sourcepos);
	~Bullet();

	void fire(int);

	int getRight() {
		return bullet.getTexture()->getSize().x * (0.5f * bullet.getScale().x);
	}
	int getLeft() {
		return bullet.getTexture()->getSize().x;
	}
	int getTop() {
		return bullet.getTexture()->getSize().y;
	}
	int getBottom() {
		return bullet.getTexture()->getSize().y * (0.5f * bullet.getScale().y);
	}

	int getCenterX() {
		return (bullet.getTexture()->getSize().x * (0.5f * bullet.getScale().x)) / 2;
	}

	sf::FloatRect boundingBox() { return bullet.getGlobalBounds(); }




	void setPos(sf::Vector2f);
	

	sf::Vector2f getPos() {
		return bullet.getPosition();
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(bullet);
	}

private:

	int rSourceY;
	int rSourceX;
	int rSourceWidht;
	int rSourceHeight;

	sf::Sprite bullet;
	sf::Sprite getSprite() const;

};

Bullet::Bullet()
{

}
Bullet::Bullet(sf::Texture& TEMP_Texture, sf::Vector2f size, sf::Vector2i sourcepos)
{


	bullet.setTexture(TEMP_Texture);
	//bullet.setOrigin(bullet.getTexture()->getSize().x * (0.5f * bullet.getScale().x), bullet.getTexture()->getSize().y * (0.5f * bullet.getScale().y));
	bullet.setScale(4.0f, 4.0f);

	rSourceY = sourcepos.y;
	rSourceX = sourcepos.x;
	rSourceWidht = size.x;
	rSourceHeight = size.y;

	//bullet.setTextureRect(sf::IntRect(rSourceX, rSourceY, rSourceWidht, rSourceHeight));
}
Bullet::~Bullet()
{

}

void Bullet::fire(int speed)
{

	bullet.move(0, -speed);

}

sf::Sprite Bullet::getSprite() const
{
	return bullet;
}

void Bullet::setPos(sf::Vector2f newPos)
{
	bullet.setPosition(newPos);
}

