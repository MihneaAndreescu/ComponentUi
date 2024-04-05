#pragma once
#include "AABBObjectGraphicsComponent.h"
#include <SFML/Graphics.hpp>

class AABBButtonObject;

class AABBButtonObjectGraphicsComponent : public AABBObjectGraphicsComponent
{
private:
	sf::Shader m_shader;
	std::shared_ptr<AABBButtonObject> m_object;

protected:
	sf::Vector2f getSize() const override;
	sf::Vector2f getCenter() const override;

	std::shared_ptr<Object> getObject() const override;

public:
	AABBButtonObjectGraphicsComponent(std::shared_ptr<AABBButtonObject> object);
	void onIdle();
	void onHover();
	void onActive();

	void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
};