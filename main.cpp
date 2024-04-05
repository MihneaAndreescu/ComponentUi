#include "Object.h"

#include "AABBButtonObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "AABBButtonObject.h"
#include "ObjectUpdateInfo.h"
#include "GraphicsComponent.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!");
    sf::View view;
    view.setSize(sf::Vector2f(-1, 1));
    view.setCenter(sf::Vector2f(0.5, 0.5));
    window.setView(view);

    sf::Texture mountainTexture;
    mountainTexture.loadFromFile("mountain.jpg");

    std::vector<std::shared_ptr<Object>> objects;

    {
        std::shared_ptr<AABBButtonObject> button = std::make_shared<AABBButtonObject>();
        button->setTexture(std::make_shared<sf::Texture>(mountainTexture));
        button->setCenter(sf::Vector2f(0.5, 0.5));
        button->setSize(sf::Vector2f(0.2, 0.2));
        objects.push_back(button);

    }

    sf::Clock frameClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            sf::sleep(sf::seconds(0.1));
        }

        float dt = frameClock.restart().asSeconds();
        ObjectUpdateInfo updateInfo;
        updateInfo.dt = dt;
        updateInfo.mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView());

        for (auto& object : objects)
        {
            object->update(updateInfo);
        }

        window.clear();
        std::vector<std::shared_ptr<GraphicsComponent>> graphicsComponents;
        for (const auto& object : objects)
        {
            for (const auto& graphicsComponent : object->getComponentsOfType<GraphicsComponent>())
            {
                graphicsComponents.push_back(graphicsComponent);
            }
        }
        for (auto& graphicsComponent : graphicsComponents)
        {
            graphicsComponent->beforeRender();
        }
        for (auto& graphicsComponent : graphicsComponents)
        {
            graphicsComponent->draw(window, sf::RenderStates::Default);
        }
        window.display();
    }

    return 0;
}
// node component -> (reper-ul sau transformul in general) pt mn: unde e cineva in raport cu parintele lui. transform: aabb, pt fiecare margine
// unde se afla fata de aabb-ul parintelui (procentual, duh)
// panel, un buton lipit de marginea din stanga la mijloc, plus altul, cu w&h relativ tot
