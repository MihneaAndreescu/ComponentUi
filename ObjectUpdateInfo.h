#pragma once
#include <SFML/Graphics.hpp>

class ObjectUpdateInfo
{
public:
	float dt;
	sf::Vector2f mousePosition;
	sf::RenderWindow* window;
	float mouseWheelDelta;
	ObjectUpdateInfo(sf::RenderWindow* window) : window(window), mouseWheelDelta(0) {

	}
};