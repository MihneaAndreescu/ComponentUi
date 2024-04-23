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

const sf::Vector2f AABBPanelObject::getSizeVirtual() const
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getSizeVirtual();
}

const sf::Vector2f AABBPanelObject::getCenterVirtual() const
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getCenterVirtual();
}