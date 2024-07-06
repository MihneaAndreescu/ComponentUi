#pragma once

#include <SFML/Graphics.hpp>

class MyTransform {
private:
    sf::Vector2f m_position;
    sf::Vector2f m_scale;
    sf::Vector2f m_origin;
public:
    MyTransform();
    void setPosition(sf::Vector2f newPosition);
    void setOrigin(sf::Vector2f newOrigin);
    void setScale(sf::Vector2f newScale);
    sf::Vector2f getPosition() const;
    sf::Vector2f getScale() const;
    sf::Vector2f getOrigin() const;
    MyTransform combine(const MyTransform& parent) const;
    sf::FloatRect getBoundingBox() const;
    void stpos(sf::Vector2f newRealPosition, const MyTransform& parent);
    void stscale(sf::Vector2f newScale, const MyTransform& parent);
};
