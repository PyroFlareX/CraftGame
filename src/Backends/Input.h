#ifndef INPUT_H
#define INPUT_H

#include "../../Engine/glad/glad/glad.h"
#include <SFML/Graphics.hpp>

namespace Input
{
	struct Inputs
	{
		bool up;
		bool down;
		int LX;
		int LY;
		int RX;
		int RY;
		bool pause;
		bool accel;
	};

	Inputs getInput();

	extern sf::RenderWindow* window;
};

#endif // INPUT_H
