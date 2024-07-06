#include "AABBShapeComponent.h"

const sf::Vector2f AABBShapeComponent::getSize() const {
	return m_object->getScale();
}

const sf::Vector2f AABBShapeComponent::getPosition() const {
	return m_object->getPosition();
}

const sf::Vector2f AABBShapeComponent::getOrigin() const {
	return m_object->getOrigin();
}

void AABBShapeComponent::setSize(sf::Vector2f newSize) {
	m_object->setScale(newSize);
}

void AABBShapeComponent::setOrigin(sf::Vector2f newOrigin) {
	m_object->setOrigin(newOrigin);
}

void AABBShapeComponent::setPosition(sf::Vector2f newPosition) {
	m_object->setPosition(newPosition);
}

AABBShapeComponent::AABBShapeComponent(std::shared_ptr<Object> object) :
	m_object(object) {
}

bool AABBShapeComponent::contains(const sf::Vector2f& point) const {
	sf::FloatRect rect = m_object->getGlobalTransform().getBoundingBox();
	return (rect.left <= point.x && point.x <= rect.left + rect.width && rect.top <= point.y && point.y <= rect.top + rect.height);
}

std::shared_ptr<Object> AABBShapeComponent::getObject() const {
	return m_object;
}
