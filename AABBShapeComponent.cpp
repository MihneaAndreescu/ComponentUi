#include "AABBShapeComponent.h"

const sf::Vector2f AABBShapeComponent::getSize() const
{
	return m_size;
}

const sf::Vector2f AABBShapeComponent::getCenter() const
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
	return abs(point.x - m_center.x) <= m_size.x * 0.5f && abs(point.y - m_center.y) <= m_size.y * 0.5f;
}

std::shared_ptr<Object> AABBShapeComponent::getObject() const
{
	return m_object;
}
