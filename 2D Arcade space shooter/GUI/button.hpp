#pragma once

#define BUTTON_HPP
#ifdef BUTTON_HPP

#include <SFML\Graphics.hpp>
#include <iostream>



	class Button : public sf::Drawable
	{

	public:

		Button();
		Button(sf::Texture&, sf::Vector2f, sf::Vector2f, sf::Vector2i, sf::Vector2i);
		~Button();

		bool mouseOver;
		void Update(sf::RenderWindow& window, sf::Event e);

		sf::Sprite getSprite() const;

		bool mouseDown = false;



	private:


		int rSourceY;
		int rSourceX;
		int rSourceWidht;
		int rSourceHeight;
		int rAddX;
		int rAddY;

		sf::Event event;


		virtual void draw(sf::RenderTarget& window, sf::RenderStates state) const
		{
			window.draw(_button, state);
		}


		sf::Sprite _button;
		sf::FloatRect buttonRect;
		sf::Vector2i mpos;

	};
#endif // BUTTON_HPP
