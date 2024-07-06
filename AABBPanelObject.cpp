#include "AABBPanelObject.h"
#include "AABBShapeComponent.h"
#include "ObjectUpdateInfo.h"
#include "AABBObjectGraphicsComponent.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

std::mt19937 rng((long long) (new char));

AABBPanelObject::AABBPanelObject()  {
}

void AABBPanelObject::create() {
    std::mt19937 gen(rng());  
    std::uniform_int_distribution<> distrib(0, 255);
    sf::Color randomColor(distrib(gen), distrib(gen), distrib(gen));
    addComponent(std::make_shared<AABBShapeComponent>(getSharedThis()));
    addComponent(std::make_shared<AABBObjectGraphicsComponent>(getSharedThis()));
    getTheUniqueComponentOfType< AABBObjectGraphicsComponent>()->setColor(randomColor);
}

sf::Vector2f compose(sf::Vector2f a, sf::Vector2f b) {
    return { a.x * b.x, a.y * b.y };
}

bool isInside(sf::Vector2f point, const sf::CircleShape& circle) {
    float radius = circle.getRadius();
    sf::Vector2f center = circle.getPosition();
    float dx = point.x - center.x;
    float dy = point.y - center.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= radius;
}

void AABBPanelObject::updateVirtual(ObjectUpdateInfo info) {
    if (restpos) {
        if (!getParent()) {
            m_transform.setPosition(*restpos);
        }
        else {
            m_transform.stpos(*restpos, getParent()->getGlobalTransform());
        }
    }
    if (restdim) {
        if (!getParent()) {
            m_transform.setScale(*restdim);
        }
        else {
            m_transform.stscale(*restdim, getParent()->getGlobalTransform());
        }
    }
    Object::updateVirtual(info);
    auto window = info.window;
    auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
    const sf::View& view = window->getView();
    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window), view);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && shapeComponent->contains(mousePos)) {
        Object::special = getSharedThis();
        Object::special2 = 0;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && shapeComponent->contains(mousePos)) {
        Object::special2 = getSharedThis();
        Object::special = 0;
    }
    if (Object::special == getSharedThis()) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!m_isDragging && shapeComponent->contains(mousePos)) {
                m_isDragging = true;
                mouseOffset = mousePos - getGlobalTransform().getPosition();
            }
        }
        else {
            m_isDragging = false;
        }
        if (m_isDragging) {
            if (!getParent()) {
                shapeComponent->setPosition(mousePos - mouseOffset);
            }
            else {
                m_transform.stpos(mousePos - mouseOffset, getParent()->getGlobalTransform());
            }
        }
        if (shapeComponent->contains(mousePos)&&sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
            float scaleFactor = 1.0f + info.mouseWheelDelta * 0.1f; 
            sf::Vector2f currentSize = shapeComponent->getSize();
            sf::Vector2f newSize = sf::Vector2f(currentSize.x * scaleFactor, currentSize.y);
            shapeComponent->setSize(newSize);
        }
        if (shapeComponent->contains(mousePos) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
            float scaleFactor = 1.0f + info.mouseWheelDelta * 0.1f;
            sf::Vector2f currentSize = shapeComponent->getSize();
            sf::Vector2f newSize = sf::Vector2f(currentSize.x, currentSize.y * scaleFactor);
            shapeComponent->setSize(newSize);
        }
    }
    if (Object::special2 == getSharedThis()) {
        sf::CircleShape circleShp = getTheUniqueComponentOfType<AABBObjectGraphicsComponent>()->m_shp;
        std::cout << "ttt : " << isInside(mousePos, circleShp) << "\n";
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!m_isDragging2 && isInside(mousePos, circleShp)) {
                m_isDragging2 = true;
                mouseOffset2 = mousePos - getGlobalTransform().getPosition();
                dif = getGlobalTransform().getPosition() - getGlobalTransform().getOrigin();
                std::cout << " = " << (getGlobalTransform().getPosition() - getGlobalTransform().getOrigin()).x << "\n";
                //mouseOffset2 = mousePos - getGlobalTransform().getPosition();
            }
        }
        else {
            m_isDragging2 = false;
        }
        if (m_isDragging2) {
            std::cout << "m_isDragging2\n";
            if (!getParent()) {
                shapeComponent->setPosition(mousePos - mouseOffset2);
                shapeComponent->setOrigin(shapeComponent->getPosition() - dif);
                assert(getGlobalTransform().getPosition() - getGlobalTransform().getOrigin() == dif);
                //shapeComponent->setPosition(mousePos - mouseOffset);
            }
            else {
                std::cout << "deadly error!\n";
                exit(0);
                //m_transform.stpos(mousePos - mouseOffset, getParent()->getGlobalTransform());
            }
        }
    }
}


void AABBPanelObject::setSize(sf::Vector2f newSize) {
    const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
    shapeComponent->setSize(newSize);
}
