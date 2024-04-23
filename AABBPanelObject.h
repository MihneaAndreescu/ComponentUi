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
	const sf::Vector2f getSizeVirtual() const;
	const sf::Vector2f getCenterVirtual() const;
	sf::Vector2f getLocalPosition() const override
	{
		return getCenterVirtual() - getSizeVirtual() * 0.5f;
	}
	virtual sf::Vector2f getLocalSize() const override
	{
		return getSizeVirtual();
	}
	void create() override;
};
