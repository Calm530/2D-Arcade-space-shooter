#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Asteroid : public sf::Transformable
{
public:
	Asteroid();
	Asteroid(sf::Texture&, sf::Vector2i, sf::Vector2i);
	~Asteroid();

	//void setSpeed(int);
	int speed;
	
	float rotSpeed;

	float hitpoints;
	void setHP(float);
	void update(sf::RenderWindow&);

	bool dead = false;


	void setPos(sf::Vector2f);
	void setSpeed(int);
	void setRotSpeed(float);

	sf::RectangleShape asteroidHitbox;

	 
	sf::Vector2f getPos() {
		return asteroid.getPosition();
	}
	float getPosY() {
		return asteroid.getPosition().y;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(asteroid);
		//window.draw(asteroidHitbox);
	}

	sf::Sprite asteroid;
	sf::Sprite getSprite() const;

};

Asteroid::Asteroid()
{

}
Asteroid::Asteroid(sf::Texture& TEMP_Texture, sf::Vector2i size, sf::Vector2i sourcepos)
{


	asteroid.setTexture(TEMP_Texture);

	sf::IntRect tex(sourcepos, size);
	asteroid.setTextureRect(tex);
	//asteroid.setOrigin(asteroid.getTexture()->getSize().x * (0.5f * asteroid.getScale().x), asteroid.getTexture()->getSize().y * (0.5f * asteroid.getScale().y));
	asteroid.setOrigin(sf::Vector2f(asteroid.getGlobalBounds().width / 2, asteroid.getGlobalBounds().height / 2));

	asteroid.setScale(3.0f, 3.0f);

	asteroidHitbox.setSize(sf::Vector2f(asteroid.getGlobalBounds().width - 10, asteroid.getGlobalBounds().height - 10));
	asteroidHitbox.setOrigin(sf::Vector2f(asteroidHitbox.getGlobalBounds().width / 2, asteroidHitbox.getGlobalBounds().height / 2));
	asteroidHitbox.setFillColor(sf::Color(255,255,255,150));

	
}
Asteroid::~Asteroid()
{

}


sf::Sprite Asteroid::getSprite() const
{
	return asteroid;
}

void Asteroid::setHP(float hp)
{
	hitpoints = hp;
}
void Asteroid::setRotSpeed(float x)
{
	rotSpeed = x;
}


void Asteroid::update(sf::RenderWindow& window)
{
	asteroidHitbox.setPosition(sf::Vector2f(asteroid.getPosition().x, asteroid.getPosition().y));

	asteroid.move(0, speed);


	asteroid.rotate(rotSpeed);

	if (asteroid.getPosition().x <= 0)
	{
		asteroid.setPosition(0, asteroid.getPosition().y);
		
	
	}
	if (asteroid.getPosition().x + asteroid.getGlobalBounds().width >= window.getSize().x)
	{
		asteroid.setPosition(window.getSize().x - asteroid.getGlobalBounds().width, asteroid.getPosition().y);
		
	}

}

void Asteroid::setPos(sf::Vector2f newPos)
{
	asteroid.setPosition(newPos);
}

void Asteroid::setSpeed(int x)
{
	speed = x;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Bullet : public sf::Transformable
{
public:
	Bullet();
	Bullet(sf::Texture&, sf::Vector2i, sf::Vector2i);
	~Bullet();

	//void setSpeed(int);
	int speed;

	float hitpoints;
	void setHP(float);
	void update();

	bool dead = false;

	void setPos(sf::Vector2f);
	void setSpeed(int);

	sf::RectangleShape bulletHitbox;


	sf::Vector2f getPos() {
		return bullet.getPosition();
	}
	float getPosY() {
		return bullet.getPosition().y;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(bullet);
		//window.draw(bulletHitbox);
	}

	sf::Sprite bullet;
	sf::Sprite getSprite() const;

};

Bullet::Bullet()
{

}
Bullet::Bullet(sf::Texture& TEMP_Texture, sf::Vector2i size, sf::Vector2i sourcepos)
{


	bullet.setTexture(TEMP_Texture);
	bullet.setTextureRect(sf::IntRect(sf::Vector2i(96, 0), sf::Vector2i(size.x, size.y)));
	//asteroid.setOrigin(asteroid.getTexture()->getSize().x * (0.5ddf * asteroid.getScale().x), asteroid.getTexture()->getSize().y * (0.5f * asteroid.getScale().y));
	bullet.setOrigin(sf::Vector2f(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2));

	bullet.setScale(3.5f, 3.5f);

	bulletHitbox.setSize(sf::Vector2f(bullet.getGlobalBounds().width - 10, bullet.getGlobalBounds().height - 10));
	bulletHitbox.setOrigin(sf::Vector2f(bulletHitbox.getGlobalBounds().width / 2, bulletHitbox.getGlobalBounds().height / 2));
	bulletHitbox.setFillColor(sf::Color(255, 255, 255, 150));


}
Bullet::~Bullet()
{

}


sf::Sprite Bullet::getSprite() const
{
	return bullet;
}

void Bullet::setHP(float hp)
{
	hitpoints = hp;
}

void Bullet::update()
{
	bulletHitbox.setPosition(sf::Vector2f(bullet.getPosition().x, bullet.getPosition().y));
	bullet.move(0, -speed);

}

void Bullet::setPos(sf::Vector2f newPos)
{
	bullet.setPosition(newPos);
}

void Bullet::setSpeed(int x)
{
	speed = x;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Star : public sf::Transformable
{
public:
	Star();
	Star(sf::Texture&, sf::Vector2i, sf::Vector2i);
	~Star();

	//void setSpeed(int);
	int speed;
	void update(sf::RenderWindow&);
	bool dead = false;

	void setPos(sf::Vector2f);
	void setSpeed(int);
	void setSize(float);

	sf::Vector2f getPos() {
		return star.getPosition();
	}
	float getPosY() {
		return star.getPosition().y;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(star);
		
	}

	sf::Sprite star;
	sf::Sprite getSprite() const;

};

Star::Star()
{

}
Star::Star(sf::Texture& TEMP_Texture, sf::Vector2i size, sf::Vector2i sourcepos)
{


	star.setTexture(TEMP_Texture);

	sf::IntRect tex(160,0, 3,3);
	star.setTextureRect(tex);
	//asteroid.setOrigin(asteroid.getTexture()->getSize().x * (0.5f * asteroid.getScale().x), asteroid.getTexture()->getSize().y * (0.5f * asteroid.getScale().y));
	star.setOrigin(sf::Vector2f(star.getGlobalBounds().width / 2, star.getGlobalBounds().height / 2));

	star.setScale(3.0f, 3.0f);



}
Star::~Star()
{

}


sf::Sprite Star::getSprite() const
{
	return star;
}

void Star::update(sf::RenderWindow& window)
{

	star.move(0, speed);


	if (star.getPosition().x <= 0)
	{
		star.setPosition(0, star.getPosition().y);

	}
	if (star.getPosition().x + star.getGlobalBounds().width >= window.getSize().x)
	{
		star.setPosition(window.getSize().x - star.getGlobalBounds().width, star.getPosition().y);

	}

}

void Star::setPos(sf::Vector2f newPos)
{
	star.setPosition(newPos);
}

void Star::setSpeed(int x)
{
	speed = x;
}
void Star::setSize(float x)
{
	star.setScale(x, x);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class BulletBar : public sf::Transformable
{
public:
	BulletBar();
	BulletBar(sf::Texture&, sf::Vector2i, sf::Vector2i);
	~BulletBar();

	//void setSpeed(int);
	int speed;
	void update(sf::RenderWindow&);
	bool dead = false;

	void setPos(sf::Vector2f);
	void setSpeed(int);
	void setSize(float);

	sf::Vector2f getPos() {
		return star.getPosition();
	}
	float getPosY() {
		return star.getPosition().y;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(star);

	}

	sf::Sprite star;
	sf::Sprite getSprite() const;

};

BulletBar::BulletBar()
{

}
BulletBar::BulletBar(sf::Texture& TEMP_Texture, sf::Vector2i size, sf::Vector2i sourcepos)
{


	star.setTexture(TEMP_Texture);

	sf::IntRect tex(160, 0, 3, 3);
	star.setTextureRect(tex);
	//asteroid.setOrigin(asteroid.getTexture()->getSize().x * (0.5f * asteroid.getScale().x), asteroid.getTexture()->getSize().y);
	star.setOrigin(sf::Vector2f(star.getGlobalBounds().width / 2, star.getGlobalBounds().height / 2));

	star.setScale(3.0f, 3.0f);



}
BulletBar::~BulletBar()
{

}


sf::Sprite BulletBar::getSprite() const
{
	return star;
}

void BulletBar::update(sf::RenderWindow& window)
{


}

void BulletBar::setPos(sf::Vector2f newPos)
{
	star.setPosition(newPos);
}

