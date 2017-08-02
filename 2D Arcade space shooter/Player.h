#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

class Player : public sf::Drawable
{
public:

	Player();
	Player(sf::Texture&, sf::Vector2f , sf::Vector2f , sf::Vector2i );
	~Player();

	sf::Vector2f getPos() {
		return player.getPosition();
	}


/*	int getSizeX() {
		return player.getScale().x;
	}
	int getSizeY() {
		return player.getScale().y;
	}
	*/
	void setPos(sf::Vector2f);

	void Movement(sf::RenderWindow&, sf::Event);
	float moveSpd = 6;
	float angle;

	void setHealth(int hitpoints)
	{
		Health = hitpoints;
	}

	sf::Sprite getSprite() const;

	sf::Sprite player;

	sf::Vector2f origin();

	sf::FloatRect boundingBox = player.getGlobalBounds();

private:


	int rSourceY;
	int rSourceX;
	int rSourceWidht;
	int rSourceHeight;
	int rAddX;
	int rAddY;

	
	int Health;


	virtual void draw(sf::RenderTarget& window, sf::RenderStates state)const
	{

		if (Health >= 0)
		{
			window.draw(player, state);
		}
	}

	sf::Clock clock;

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player()
{
}

Player::Player(sf::Texture& TEMP_Texture, sf::Vector2f posi, sf::Vector2f size, sf::Vector2i sourcepos)
{

	player.setTexture(TEMP_Texture);
	//player.setPosition(posi);

	player.setOrigin(sf::Vector2f(player.getTexture()->getSize().x * 0.5, player.getTexture()->getSize().y * 0.5));

	player.setScale(2.7f, 2.7f);
	 
	

	rSourceY = sourcepos.y;
	rSourceX = sourcepos.x;
	rSourceWidht = size.x;
	rSourceHeight = size.y;

	player.setTextureRect(sf::IntRect(rSourceX, rSourceY, rSourceWidht, rSourceHeight));
	
}

Player::~Player()
{
}


void Player::setPos(sf::Vector2f newPos)
{
	player.setPosition(newPos);
}

sf::Sprite Player::getSprite() const
{
	return player;
}

sf::Vector2f Player::origin()
{
	

	return player.getOrigin();

}

void Player::Movement(sf::RenderWindow& window, sf::Event event)
{
	

	float positionX;
	float positionY;

	float speed;
	
	

	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	float targetX;
	float targetY;
	float angleX;
	float angleY;
	float distance;
	float directionX;
	float directionY;
	float velocityX;
	float velocityY;

	positionX = player.getPosition().x;
	positionY = player.getPosition().y;

/*
	targetX = mousePos.x;
	targetY = mousePos.y;
	angleX = mousePos.x - (positionX + (player.getGlobalBounds().width) / (player.getScale().x));
	angleY = mousePos.y - (positionY + (player.getGlobalBounds().height)/ (player.getScale().y *2));
	distance = sqrt((angleX * angleX) + (angleY * angleY));
	directionX = angleX / distance;
	directionY = angleY / distance;
	velocityX = directionX * speed;
	velocityY = directionY * speed;
*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.move(0, -moveSpd);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.move(0, moveSpd);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.move(-moveSpd, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.move(moveSpd, 0);
	}

	
		//if(player.getPosition()!=window.mapPixelToCoords(sf::Mouse::getPosition(window)))
		//player.move(velocityX, velocityY);
	
	if (player.getPosition().x <= 0)
	{
		player.setPosition(0, player.getPosition().y);
	}
	if (player.getPosition().x + player.getGlobalBounds().width >= window.getSize().x)
	{
		player.setPosition(window.getSize().x - player.getGlobalBounds().width, player.getPosition().y);
	}

	if (player.getPosition().y <= 0)
	{
		player.setPosition(player.getPosition().x, 0);
	}
	if (player.getPosition().y + player.getGlobalBounds().height >= window.getSize().y)
	{
		player.setPosition(player.getPosition().x, window.getSize().y - player.getGlobalBounds().height);
	}

}
