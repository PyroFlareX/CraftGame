#pragma once

#include <SFML/Graphics.hpp>

// GLAD
#include "../../Engine/Engine.h"

class Context
{
public:
	Context();

	void clear();
	void update();
	void close();
	void initAPI();
	bool isOpen();

	sf::RenderWindow* getContext();

	~Context();

private:
	sf::RenderWindow m_window;
};
