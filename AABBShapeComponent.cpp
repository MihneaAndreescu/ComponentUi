#include "AABBShapeComponent.h"

const sf::Vector2f AABBShapeComponent::getSizeVirtual() const
{
	return m_size;
}

const sf::Vector2f AABBShapeComponent::getCenterVirtual() const
{
	return m_center;
}

void AABBShapeComponent::setSize(sf::Vector2f newSize)
{
	m_size = newSize;
}

void AABBShapeComponent::setCenter(sf::Vector2f newCenter)
{
	m_center = newCenter;
}

AABBShapeComponent::AABBShapeComponent(std::shared_ptr<Object> object) :
	m_object(object)
{
}

bool AABBShapeComponent::contains(const sf::Vector2f& point) const
{
	auto [position, size] = m_object->getGlobalPositionAndSize();
	sf::Vector2f center = position + size * 0.5f;
	return abs(point.x - center.x) <= size.x * 0.5f && abs(point.y - center.y) <= size.y * 0.5f;
}

std::shared_ptr<Object> AABBShapeComponent::getObject() const
{
	return m_object;
}
