#pragma once

#include <SFML/Graphics.hpp>
#include "ButtonObject.h"

class AABBButtonObject : public ButtonObject
{
public:
	AABBButtonObject();
	void setTexture(std::shared_ptr<sf::Texture> newTexture);
	void onIdle() override; 
	void onHover() override;
	void onActive() override;
	void updateVirtual(ObjectUpdateInfo info) override;
	void setSize(sf::Vector2f newSize);
	void setCenter(sf::Vector2f newCenter);
	const sf::Vector2f getSize() const;
	const sf::Vector2f getCenter() const;
	sf::Vector2f getLocalPosition() const override
	{
		return getCenter() - getSize() * 0.5f;
	}
	virtual sf::Vector2f getLocalSize() const override
	{
		return getSize();
	}
	void create() override;
};
