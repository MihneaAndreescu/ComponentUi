#pragma once
#include "GraphicsComponent.h"
#include <memory>

class AABBObjectGraphicsComponent : public GraphicsComponent
{
private:
	sf::VertexArray m_vertexArray;
	std::shared_ptr<sf::Texture> m_texture;
protected:
	virtual sf::Vector2f getSize() const = 0;
	virtual sf::Vector2f getCenter() const = 0;
public:
	AABBObjectGraphicsComponent();
	void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
	void beforeRender() override;
	void setTexture(std::shared_ptr<sf::Texture> newTexture);
};