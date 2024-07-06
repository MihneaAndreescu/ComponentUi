#pragma once

#include "ShapeComponent.h"
#include "MyTransform.h"

class AABBShapeComponent : public ShapeComponent {
private:
	std::shared_ptr<Object> m_object;
protected:
	std::shared_ptr<Object> getObject() const override;
public:
	AABBShapeComponent(std::shared_ptr<Object> object);
	const sf::Vector2f getSize() const;
	const sf::Vector2f getOrigin() const;
	const sf::Vector2f getPosition() const;
	void setSize(sf::Vector2f newSize);
	void setOrigin(sf::Vector2f newOrigin);
	void setPosition(sf::Vector2f newPosition);
	bool contains(const sf::Vector2f& point) const override;
};
