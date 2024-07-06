#include "MyTransform.h"

MyTransform::MyTransform()
    : m_position(0, 0), m_scale(1, 1), m_origin(0, 0) {
}

void MyTransform::setPosition(sf::Vector2f newPosition) {
    m_position = newPosition;
}

void MyTransform::setOrigin(sf::Vector2f newOrigin) {
    m_origin = newOrigin;
}

void MyTransform::setScale(sf::Vector2f newScale) {
    m_scale = newScale;
}

sf::Vector2f MyTransform::getPosition() const {
    return m_position;
}

sf::Vector2f MyTransform::getScale() const {
    return m_scale;
}

sf::Vector2f MyTransform::getOrigin() const {
    return m_origin;
}

MyTransform MyTransform::combine(const MyTransform& parent) const {
    MyTransform result;
    result.m_position = parent.m_position;
    result.m_position -= sf::Vector2f(parent.m_scale.x * parent.m_origin.x, parent.m_scale.y * parent.m_origin.y);
    result.m_position += sf::Vector2f(parent.m_scale.x * m_position.x, parent.m_scale.y * m_position.y);
    result.m_scale = sf::Vector2f(m_scale.x * parent.m_scale.x, m_scale.y * parent.m_scale.y);
    result.m_origin = m_origin;
    return result;
}

sf::FloatRect MyTransform::getBoundingBox() const {
    sf::Vector2f top_left(m_position.x - m_origin.x * m_scale.x, m_position.y - m_origin.y * m_scale.y);
    sf::Vector2f size(m_scale.x, m_scale.y);
    return sf::FloatRect(top_left, size);
}

/*
setRealPosition(newRealPosition);
vreau m_transform in asa fel incat
m_transform.combine(partrans).position = newRealPosition;


*/

#include <cassert>

void MyTransform::stpos(sf::Vector2f newRealPosition, const MyTransform& parent) {
    //sf::Vector2f ret;
    //ret = sf::Vector2f(parent.m_scale.x * m_position.x, parent.m_scale.y * m_position.y);
    //assert(ret == newRealPosition - parent.m_position + sf::Vector2f(parent.m_scale.x * parent.m_origin.x, parent.m_scale.y * parent.m_origin.y));
    sf::Vector2f value = newRealPosition - parent.m_position + sf::Vector2f(parent.m_scale.x * parent.m_origin.x, parent.m_scale.y * parent.m_origin.y);
    m_position.x = value.x / parent.m_scale.x;
    m_position.y = value.y / parent.m_scale.y;
}

void MyTransform::stscale(sf::Vector2f newScale, const MyTransform& parent) {
    m_scale = sf::Vector2f(newScale.x / parent.m_scale.x, newScale.y / parent.m_scale.y);
}