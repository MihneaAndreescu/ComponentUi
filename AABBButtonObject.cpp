#include "AABBButtonObject.h"
#include "AABBShapeComponent.h"
#include "AABBButtonObjectGraphicsComponent.h"
#include "ObjectUpdateInfo.h"

AABBButtonObject::AABBButtonObject()
{
	auto shape = std::make_shared<AABBShapeComponent>(std::make_shared<Object>(*this));
	addComponent(shape);
	std::shared_ptr<AABBButtonObjectGraphicsComponent> graphicsComponent = std::make_shared<AABBButtonObjectGraphicsComponent>(std::make_shared<AABBButtonObject>(*this));
	addComponent(graphicsComponent);
}

void AABBButtonObject::onIdle()
{
	getTheUniqueComponentOfType<AABBButtonObjectGraphicsComponent>()->onIdle();
}

void AABBButtonObject::onHover()
{
	getTheUniqueComponentOfType<AABBButtonObjectGraphicsComponent>()->onHover();
}

void AABBButtonObject::onActive()
{
	getTheUniqueComponentOfType<AABBButtonObjectGraphicsComponent>()->onActive();
}

void AABBButtonObject::setTexture(std::shared_ptr<sf::Texture> newTexture)
{
	const auto graphicsComponent = getTheUniqueComponentOfType<AABBButtonObjectGraphicsComponent>();
	graphicsComponent->setTexture(newTexture);
}

void AABBButtonObject::setSize(sf::Vector2f newSize)
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	shapeComponent->setSize(newSize);
}

void AABBButtonObject::setCenter(sf::Vector2f newCenter)
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	shapeComponent->setCenter(newCenter);
}

const sf::Vector2f& AABBButtonObject::getSize() const
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getSize();
}

const sf::Vector2f& AABBButtonObject::getCenter() const
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getCenter();
}

#include <iostream>

void AABBButtonObject::updateVirtual(ObjectUpdateInfo info) 
{
	std::cout << "aabb button object\n";
	ButtonObject::updateVirtual(info);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
		shapeComponent->setCenter(shapeComponent->getCenter() + sf::Vector2f(0, -1) * 1.0f * info.dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
		shapeComponent->setCenter(shapeComponent->getCenter() + sf::Vector2f(0, 1) * 1.0f * info.dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
		shapeComponent->setCenter(shapeComponent->getCenter() + sf::Vector2f(-1, 0) * 1.0f * info.dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
		shapeComponent->setCenter(shapeComponent->getCenter() + sf::Vector2f(+1, 0) * 1.0f * info.dt);
	}
}