#include "AABBObjectGraphicsComponent.h"


AABBObjectGraphicsComponent::AABBObjectGraphicsComponent()
{
}

#include <iostream>

void AABBObjectGraphicsComponent::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	if (m_texture)
	{
		renderStates.texture = m_texture.get();
	}
	renderTarget.draw(m_vertexArray, renderStates);
}



void AABBObjectGraphicsComponent::beforeRender()
{
	m_vertexArray.setPrimitiveType(sf::Quads);
	m_vertexArray.clear();

	m_vertexArray.append(sf::Vertex(sf::Vector2f(getCenter().x - getSize().x * 0.5f, getCenter().y - getSize().y * 0.5)));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(getCenter().x - getSize().x * 0.5f, getCenter().y + getSize().y * 0.5)));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(getCenter().x + getSize().x * 0.5f, getCenter().y + getSize().y * 0.5)));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(getCenter().x + getSize().x * 0.5f, getCenter().y - getSize().y * 0.5)));

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