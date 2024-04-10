#include "AABBPanelObject.h"
#include "AABBShapeComponent.h"
#include "ObjectUpdateInfo.h"
#include "AABBShapeComponent.h"
#include "AABBObjectGraphicsComponent.h"

AABBPanelObject::AABBPanelObject()
{
	auto shape = std::make_shared<AABBShapeComponent>(std::make_shared<Object>(*this));
	addComponent(shape);
	std::shared_ptr<AABBObjectGraphicsComponent> graphicsComponent = std::make_shared<AABBObjectGraphicsComponent>(std::make_shared<Object>(*this));
	addComponent(graphicsComponent);
}


void AABBPanelObject::updateVirtual(ObjectUpdateInfo info)
{
	Object::updateVirtual(info);
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

const sf::Vector2f& AABBPanelObject::getSize() const
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getSize();
}

const sf::Vector2f& AABBPanelObject::getCenter() const
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getCenter();
}