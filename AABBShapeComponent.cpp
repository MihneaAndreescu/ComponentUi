#include "AABBShapeComponent.h"

sf::Vector2f AABBShapeComponent::intervalize(sf::Vector2f p, sf::Vector2f low, sf::Vector2f high) const
{
	p.x = std::max(p.x, low.x);
	p.y = std::max(p.y, low.y);
	p.x = std::min(p.x, high.x);
	p.y = std::min(p.y, high.y);
	return p;
}

const sf::Vector2f AABBShapeComponent::getSize() const
{
	return m_size;
}

const sf::Vector2f AABBShapeComponent::getPosition() const
{
	return m_center - m_size * 0.5f;
}

const sf::Vector2f AABBShapeComponent::getCenter() const
{
	return m_center;
}

void AABBShapeComponent::setSize(sf::Vector2f newSize)
{
	m_size = newSize;
	m_size = intervalize(m_size, sf::Vector2f(0, 0), 2.0f * sf::Vector2f(std::min(m_center.x, 1 - m_center.x), std::min(m_center.y, 1 - m_center.y)));
}

void AABBShapeComponent::setCenter(sf::Vector2f newCenter)
{
	m_center = newCenter;
	m_center = intervalize(m_center, m_size * 0.5f, sf::Vector2f(1, 1) - m_size * 0.5f);
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
