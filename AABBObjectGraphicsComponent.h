#pragma once
#include "GraphicsComponent.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <memory>

class AABBObjectGraphicsComponent : public GraphicsComponent {
private:
    std::shared_ptr<Object> m_object;
    std::shared_ptr<sf::Texture> m_texture;
    sf::VertexArray m_vertexArray;
    sf::Color m_color = sf::Color::White;
    std::shared_ptr<sf::Color> borderColor;
public:
    sf::CircleShape m_shp;
    AABBObjectGraphicsComponent(std::shared_ptr<Object> object);
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;
    void beforeRender();
    void setTexture(std::shared_ptr<sf::Texture> newTexture);
    sf::Vector2f getSize() const;
    std::shared_ptr<Object> getObject() const;
    void setColor(sf::Color color);
};

