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
/*	int getSizeX() {ssssd dd dssasasd
		return player.getScale().x;
	}
	int getSizeY() {
		return player.getScale().y;
	}
	*/
	void setPos(sf::Vector2f);

	void Movement(sf::RenderWindow&, sf::Event);
	float moveSpd = 6.5;

	int Health = 4;
	
	void setHealth(int hitpoints)
	{
		Health = hitpoints;
	}

	sf::Sprite getSprite() const;

	sf::Sprite player;

	sf::Vector2f origin();

	sf::FloatRect boundingBox() { return player.getGlobalBounds(); }

	int getRight() {
		return player.getTexture()->getSize().x * (0.5f * player.getScale().x);
	}


private:


	int rSourceY;
	int rSourceX;
	int rSourceWidht;
	int rSourceHeight;
	int rAddX;
	int rAddY;

	


	

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
	
	if (Health <= 0)
	{
		Health = 0;
	}
	float positionX;
	float positionY;

	float speed;
	
	

	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));


	positionX = player.getPosition().x;
	positionY = player.getPosition().y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.move(0, -moveSpd);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.move(0, moveSpd);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.move(-moveSpd, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.move(moveSpd, 0);
		
	}

	
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
