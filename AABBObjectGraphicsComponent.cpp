#include "AABBObjectGraphicsComponent.h"
#include "AABBShapeComponent.h"
#include "Object.h"
#include "MyTransform.h"

AABBObjectGraphicsComponent::AABBObjectGraphicsComponent(std::shared_ptr<Object> object) :
	m_object(object) {
}

std::shared_ptr<Object> AABBObjectGraphicsComponent::getObject() const {
	return m_object;
}

#include <iostream>

void AABBObjectGraphicsComponent::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
	if (m_texture) {
		renderStates.texture = m_texture.get();
	}
	renderTarget.draw(m_vertexArray, renderStates);
	sf::RectangleShape borderRect;
	borderRect.setPosition(m_vertexArray[0].position);
	borderRect.setSize(sf::Vector2f(m_vertexArray[2].position.x - m_vertexArray[0].position.x, m_vertexArray[2].position.y - m_vertexArray[0].position.y));
	borderRect.setFillColor(sf::Color::Transparent);
	borderRect.setOutlineThickness(0.01f);
	if (borderColor) {	
		borderRect.setOutlineColor(*borderColor);
		renderTarget.draw(borderRect, renderStates);
	}
	if (getObject()->restpos) {
		sf::Vector2f size = borderRect.getSize();
		sf::Vector2f pos = borderRect.getPosition();
		sf::Vertex line1[] = {
			sf::Vertex(pos, m_color),
			sf::Vertex(sf::Vector2f(pos.x + size.x, pos.y + size.y), m_color)
		};
		sf::Vertex line2[] = {
			sf::Vertex(sf::Vector2f(pos.x, pos.y + size.y), m_color),
			sf::Vertex(sf::Vector2f(pos.x + size.x, pos.y), m_color)
		};
		line1[0].color = line1[1].color = line2[0].color = line2[1].color = sf::Color::Blue;
		renderTarget.draw(line1, 2, sf::Lines, renderStates);
		renderTarget.draw(line2, 2, sf::Lines, renderStates);
	}
	if (getObject()->restdim) {
		sf::Vector2f size = borderRect.getSize();
		sf::Vector2f pos = borderRect.getPosition();
		sf::Vertex line1[] = {
			sf::Vertex(sf::Vector2f(pos.x + size.x * 0.5f, pos.y), m_color),
			sf::Vertex(sf::Vector2f(pos.x + size.x * 0.5f, pos.y + size.y), m_color)
		};
		sf::Vertex line2[] = {
			sf::Vertex(sf::Vector2f(pos.x, pos.y + size.y * 0.5f), m_color),
			sf::Vertex(sf::Vector2f(pos.x + size.x, pos.y + size.y * 0.5f), m_color)
		};
		line1[0].color = line1[1].color = line2[0].color = line2[1].color = sf::Color::Blue;
		renderTarget.draw(line1, 2, sf::Lines, renderStates);
		renderTarget.draw(line2, 2, sf::Lines, renderStates);
	}
	renderTarget.draw(m_shp, renderStates);
}

sf::Vector2f AABBObjectGraphicsComponent::getSize() const {
	const auto shapeComponent = m_object->getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getSize();
}

void AABBObjectGraphicsComponent::setColor(sf::Color color) {
	m_color = color;
}

void AABBObjectGraphicsComponent::beforeRender() {
	sf::FloatRect boundingBox = m_object->getGlobalTransform().getBoundingBox();
	m_shp.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
	m_shp.setRadius(0.02f);
	m_shp.setOrigin(m_shp.getRadius() * sf::Vector2f(1, 1));
	if (Object::special2 == getObject()) {
		m_shp.setFillColor(sf::Color::Red);
	}
	else {
		m_shp.setFillColor(sf::Color::Cyan);
	}
	borderColor = 0;
	if (Object::special == getObject()) {
		borderColor = std::make_shared<sf::Color>(sf::Color::Green);
	}
	m_vertexArray.setPrimitiveType(sf::Quads);
	m_vertexArray.clear();
	sf::Vector2f topLeft(boundingBox.left, boundingBox.top);
	sf::Vector2f bottomRight(boundingBox.left + boundingBox.width, boundingBox.top + boundingBox.height);
	m_vertexArray.setPrimitiveType(sf::Quads);
	m_vertexArray.resize(4);
	for (std::size_t i = 0; i < 4; i++) {
		m_vertexArray[i].color = m_color;
	}
	m_vertexArray[0].position = topLeft;
	m_vertexArray[1].position = sf::Vector2f(topLeft.x, bottomRight.y);
	m_vertexArray[2].position = bottomRight;
	m_vertexArray[3].position = sf::Vector2f(bottomRight.x, topLeft.y);
	assert((int)m_vertexArray.getVertexCount() == 4);
	if (m_texture) {
		m_vertexArray[0].texCoords = sf::Vector2f(0, 0);
		m_vertexArray[1].texCoords = sf::Vector2f(0, m_texture->getSize().y);
		m_vertexArray[2].texCoords = sf::Vector2f(m_texture->getSize().x, m_texture->getSize().y);
		m_vertexArray[3].texCoords = sf::Vector2f(m_texture->getSize().x, 0);
	}
}

void AABBObjectGraphicsComponent::setTexture(std::shared_ptr<sf::Texture> newTexture) {
	m_texture = newTexture;
}