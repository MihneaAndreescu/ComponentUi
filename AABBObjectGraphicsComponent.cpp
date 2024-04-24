#include "AABBObjectGraphicsComponent.h"
#include "AABBShapeComponent.h"
#include "Object.h"

AABBObjectGraphicsComponent::AABBObjectGraphicsComponent(std::shared_ptr<Object> object) :
	m_object(object)
{
}

std::shared_ptr<Object> AABBObjectGraphicsComponent::getObject() const
{
	return m_object;
}

void AABBObjectGraphicsComponent::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	if (m_texture)
	{
		renderStates.texture = m_texture.get();
	}
	renderTarget.draw(m_vertexArray, renderStates);
}

sf::Vector2f AABBObjectGraphicsComponent::getSize() const
{
	const auto shapeComponent = m_object->getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getSize();
}

sf::Vector2f AABBObjectGraphicsComponent::getCenter() const
{
	const auto shapeComponent = m_object->getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getCenter();
}

void AABBObjectGraphicsComponent::beforeRender()
{
	m_vertexArray.setPrimitiveType(sf::Quads);
	m_vertexArray.clear();

	auto [position, size] = m_object->getGlobalPositionAndSize();
	
	m_vertexArray.append(sf::Vertex(sf::Vector2f(position.x, position.y)));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(position.x, position.y + size.y)));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(position.x + size.x, position.y + size.y)));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(position.x + size.x, position.y)));
	assert((int)m_vertexArray.getVertexCount() == 4);
	if (m_texture)
	{
		m_vertexArray[0].texCoords = sf::Vector2f(0, 0);
		m_vertexArray[1].texCoords = sf::Vector2f(0, m_texture.get()->getSize().y);
		m_vertexArray[2].texCoords = sf::Vector2f(m_texture.get()->getSize().x, m_texture.get()->getSize().y);
		m_vertexArray[3].texCoords = sf::Vector2f(m_texture.get()->getSize().x, 0);
	}
}

void AABBObjectGraphicsComponent::setTexture(std::shared_ptr<sf::Texture> newTexture)
{
	m_texture = newTexture;
}