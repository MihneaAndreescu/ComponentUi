#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class ObjectUpdateInfo;

class AABBPanelObject : public Object
{
public:
	AABBPanelObject();
	void updateVirtual(ObjectUpdateInfo updateInfo) override;
	void setSize(sf::Vector2f newSize);
	void setCenter(sf::Vector2f newCenter);
	sf::Vector2f getLocalPosition() const override;
	virtual sf::Vector2f getLocalSize() const override;
	void create() override;
};
