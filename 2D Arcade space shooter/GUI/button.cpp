#include "button.hpp"
	Button::Button()
	{

	}

	Button::Button(sf::Texture& TEMP_Texture, sf::Vector2f posi, sf::Vector2f size, sf::Vector2i sourcepos, sf::Vector2i TexSize)
	{
		_button.setTexture(TEMP_Texture);
		_button.setPosition(posi);
		_button.setScale(size);




		rSourceWidht = sourcepos.x;
		rSourceHeight = sourcepos.y;
		rAddX = size.x;
		rAddY = size.y;

		_button.setTextureRect(sf::IntRect(rSourceX, rSourceY, rSourceWidht, rSourceHeight));
	}
	Button::~Button()
	{

	}

	sf::Sprite Button::getSprite() const
	{
		return _button;
	}

	void Button::Update(sf::RenderWindow& window, sf::Event e)
	{
		mouseDown = false;

		sf::Vector2i mpos = sf::Mouse::getPosition(window);


		if (_button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))

		{
			_button.setTextureRect(sf::IntRect(rSourceX + rAddX * 2, rSourceY, rSourceWidht, rSourceHeight));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				_button.setTextureRect(sf::IntRect(rSourceX + rAddX, rSourceY, rSourceWidht, rSourceHeight));
				mouseDown = true;

			}
			if (event.type == sf::Event::EventType::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (mouseDown)
					{

						mouseDown = false;
					}
				}
			}

		}
		else
		{

			_button.setTextureRect(sf::IntRect(rSourceX, rSourceY, rSourceWidht, rSourceHeight));
		}
	}