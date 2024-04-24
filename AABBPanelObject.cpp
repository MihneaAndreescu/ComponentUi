#include "AABBPanelObject.h"
#include "AABBShapeComponent.h"
#include "ObjectUpdateInfo.h"
#include "AABBShapeComponent.h"
#include "AABBObjectGraphicsComponent.h"

#include <iostream>

AABBPanelObject::AABBPanelObject()
{
}

void AABBPanelObject::create() 
{
	addComponent(std::make_shared<AABBShapeComponent>(getSharedThis()));
	addComponent(std::make_shared<AABBObjectGraphicsComponent>(getSharedThis()));
}

void AABBPanelObject::updateVirtual(ObjectUpdateInfo info)
{
	Object::updateVirtual(info);
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	sf::Vector2f center = shapeComponent->getCenter();
	center += (sf::Vector2f(0, -1) * 1.0f * info.dt) * ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) * 1.0f);
	center += sf::Vector2f(0, 1) * 1.0f * info.dt * ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) * 1.0f);
	center += sf::Vector2f(-1, 0) * 1.0f * info.dt * ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) * 1.0f);
	center += sf::Vector2f(+1, 0) * 1.0f * info.dt * ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) * 1.0f);
	shapeComponent->setCenter(center);
	sf::Vector2f size = shapeComponent->getSize();
	float scale = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		scale *= pow(2.0f, info.dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		scale *= pow(1.0f / 2.0f, info.dt);
	}
	size.x *= scale;
	size.y *= scale;
	shapeComponent->setSize(size);
}

void AABBPanelObject::setSize(sf::Vector2f newSize)
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	shapeComponent->setSize(newSize);
}

void AABBPanelObject::setCenter(sf::Vector2f newCenter)
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	shapeComponent->setCenter(newCenter);
}

sf::Vector2f AABBPanelObject::getLocalPosition() const
{
	return getTheUniqueComponentOfType<AABBShapeComponent>()->getPosition();
}

sf::Vector2f AABBPanelObject::getLocalSize() const
{
	return getTheUniqueComponentOfType<AABBShapeComponent>()->getSize();
}