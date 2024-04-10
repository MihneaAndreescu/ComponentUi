#pragma once
#include "GraphicsComponent.h"
#include <memory>

class AABBObjectGraphicsComponent : public GraphicsComponent
{
private:
	sf::VertexArray m_vertexArray;
	std::shared_ptr<sf::Texture> m_texture;
	std::shared_ptr<Object> m_object;

protected:
	
	sf::Vector2f getSize() const;
	sf::Vector2f getCenter() const;

	std::shared_ptr<Object> getObject() const override;

public:
	AABBObjectGraphicsComponent(std::shared_ptr<Object> object);
	void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
	void beforeRender() override;
	void setTexture(std::shared_ptr<sf::Texture> newTexture);
};