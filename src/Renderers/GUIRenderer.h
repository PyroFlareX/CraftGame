#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class GUIRenderer
{
public:
	GUIRenderer();

	void addElement(sf::Sprite widget, sf::Vector2i pos);

	~GUIRenderer();
private:
	std::vector<sf::Drawable> m_elements;
};