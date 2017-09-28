#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Asteroid.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include "GUI\button.hpp"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <algorithm>
#include <string>
#include <cctype>
#include <sstream>

#include "Game.h"



int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 600), "D3RP", sf::Style::Close);
	window.setFramerateLimit(60);

	sf::Event event;

	Game game();

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{

			

			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}





		window.clear();

		window.display();
		}
	

	return 0;
}