#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class ObjectUpdateInfo;

class AABBPanelObject : public Object
{
public:
	AABBPanelObject();
	void update(ObjectUpdateInfo updateInfo) override;

	void setSize(sf::Vector2f newSize);
	void setCenter(sf::Vector2f newCenter);
	const sf::Vector2f& getSize() const;
	const sf::Vector2f& getCenter() const;
};
