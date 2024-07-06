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
	void setPosition(sf::Vector2f newPosition);
	void setOrigin(sf::Vector2f newOrigin);
	void create() override;
};
