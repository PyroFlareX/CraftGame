#include "Input.h"

namespace Input
{
	sf::RenderWindow* window;

	Inputs getInput()
	{
		double x = 0, y = 0;
		Inputs input = { false, false, 0, 0, 0, 0, false, false };

		static bool enableCursor = false;
		enableCursor = false;
		
		window->setMouseCursorVisible(enableCursor);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			input.LY++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			input.LY--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			input.LX--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			input.LX++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			input.up = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			input.down = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			input.pause = true;
			window->setMouseCursorVisible(enableCursor);
			enableCursor = !enableCursor;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			input.accel = true;
		}

		if (!enableCursor)
		{
			sf::Vector2i mouse = sf::Mouse::getPosition(*window);
			sf::Mouse::setPosition(sf::Vector2i(100, 100),*window);
			input.RY += mouse.y - 100;
			input.RX += mouse.x - 100;
		}
		return input;
	}
}
