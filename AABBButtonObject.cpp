#include "AABBButtonObject.h"
#include "AABBShapeComponent.h"
#include "AABBButtonObjectGraphicsComponent.h"
#include "ObjectUpdateInfo.h"

AABBButtonObject::AABBButtonObject()
{

}

void AABBButtonObject::create()
{
	addComponent(std::make_shared<AABBShapeComponent>(getSharedThis()));
	addComponent(std::make_shared<AABBButtonObjectGraphicsComponent>(std::dynamic_pointer_cast<AABBButtonObject>(getSharedThis())));
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

void AABBButtonObject::updateVirtual(ObjectUpdateInfo info)
{
	ButtonObject::updateVirtual(info);
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	sf::Vector2f center = shapeComponent->getCenter();
	center += (sf::Vector2f(0, -1) * 1.0f * info.dt) * ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * 1.0f);
	center += sf::Vector2f(0, 1) * 1.0f * info.dt * ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) * 1.0f);
	center += sf::Vector2f(-1, 0) * 1.0f * info.dt * ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) * 1.0f);
	center += sf::Vector2f(+1, 0) * 1.0f * info.dt * ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * 1.0f);
	shapeComponent->setCenter(center);
}

sf::Vector2f AABBButtonObject::getLocalPosition() const
{
	return getTheUniqueComponentOfType<AABBShapeComponent>()->getPosition();
}

sf::Vector2f AABBButtonObject::getLocalSize() const 
{
	return getTheUniqueComponentOfType<AABBShapeComponent>()->getSize();
}