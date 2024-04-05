#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ShapeComponent : public Component
{
public:
	virtual ~ShapeComponent() = default;
	virtual bool contains(const sf::Vector2f& point) const = 0;
};