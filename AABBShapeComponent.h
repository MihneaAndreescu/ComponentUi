#pragma once

#include "ShapeComponent.h"

class AABBShapeComponent : public ShapeComponent
{
private:
	sf::Vector2f intervalize(sf::Vector2f p, sf::Vector2f low, sf::Vector2f high) const;
	sf::Vector2f m_center;
	sf::Vector2f m_size;
	std::shared_ptr<Object> m_object;
protected:
	std::shared_ptr<Object> getObject() const override;
public:
	AABBShapeComponent(std::shared_ptr<Object> object);
	const sf::Vector2f getSize() const;
	const sf::Vector2f getCenter() const;
	const sf::Vector2f getPosition() const;
	void setSize(sf::Vector2f newSize);
	void setCenter(sf::Vector2f newCenter);
	bool contains(const sf::Vector2f& point) const override;
};
