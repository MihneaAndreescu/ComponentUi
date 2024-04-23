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
	const sf::Vector2f getSize() const;
	const sf::Vector2f getCenter() const;
	sf::Vector2f getLocalPosition() const override
	{
		return getSize();
	}
	virtual sf::Vector2f getLocalSize() const override
	{
		return getSize();
	}
	void create() override;
};
