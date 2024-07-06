#include <iostream>
#include <cmath> 
#include <numbers>
#include "AABBButtonObject.h"
#include "ObjectUpdateInfo.h"
#include "GraphicsComponent.h"
#include "AABBPanelObject.h"
#include <SFML/Graphics.hpp>
#include "MyTransform.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!");
    sf::View view;
    view.setSize(sf::Vector2f(1, 1));
    view.setCenter(sf::Vector2f(0.5, 0.5));
    window.setView(view);
    sf::Texture mountainTexture;
    mountainTexture.loadFromFile("mountain.jpg");
    std::vector<std::shared_ptr<Object>> objects, allBuiltObjects;
    {
        std::shared_ptr<AABBPanelObject> panel1 = std::make_shared<AABBPanelObject>();
        panel1->create();
        panel1->setPosition(sf::Vector2f(0.1f, 0.1f));
        panel1->setSize(sf::Vector2f(0.3f, 0.3f));
        objects.push_back(panel1);
        allBuiltObjects.push_back(panel1);

        std::shared_ptr<AABBPanelObject> panel2 = std::make_shared<AABBPanelObject>();
        panel2->create();
        panel2->setPosition(sf::Vector2f(0.5f, 0.5f));  
        panel2->setSize(sf::Vector2f(0.8f, 0.8f)); 
        allBuiltObjects.push_back(panel2);

        std::shared_ptr<AABBPanelObject> panel3 = std::make_shared<AABBPanelObject>();
        panel3->create();
        panel3->setPosition(sf::Vector2f(0.1f, 0.1f)); 
        panel3->setSize(sf::Vector2f(0.2f, 0.2f));
        panel2->addChild(panel3);  
        allBuiltObjects.push_back(panel3);


        std::shared_ptr<AABBPanelObject> panel4 = std::make_shared<AABBPanelObject>();
        panel4->create();
        panel4->setPosition(sf::Vector2f(0.4f, 0.1f)); 
        panel4->setSize(sf::Vector2f(0.2f, 0.2f));
        panel4->setOrigin(sf::Vector2f(0.1f, 0.4f));
        panel2->addChild(panel4);  
        allBuiltObjects.push_back(panel4);


        std::shared_ptr<AABBPanelObject> panel5 = std::make_shared<AABBPanelObject>();
        panel5->create();
        panel5->setPosition(sf::Vector2f(0.1f, 0.4f));  
        panel5->setSize(sf::Vector2f(0.2f, 0.2f));
        panel5->setPosition(sf::Vector2f(0.3, 0.5f));

        panel2->addChild(panel5);  
        allBuiltObjects.push_back(panel5);

        panel5->restpos = std::make_shared<sf::Vector2f>(panel5->getGlobalTransform().getPosition());
        panel4->restdim = std::make_shared<sf::Vector2f>(panel4->getGlobalTransform().getScale());
        
        objects.push_back(panel2); 
    }
    sf::Clock frameClock, fpsClock;
    int fps = 0;
    std::shared_ptr<Object> ant = Object::special;
    std::cout << "special node = " << Object::special << "\n";
    while (window.isOpen()){
        float mouseWheelDelta = 0.0f;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                mouseWheelDelta += event.mouseWheelScroll.delta; 
            }
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        float dt = frameClock.restart().asSeconds();
        if (fpsClock.getElapsedTime().asSeconds() >= 1) {
            std::cout << "fps = " << fps << "\n";
            fps = 0;
            fpsClock.restart();
        }
        fps++;
        if (ant != Object::special) {
            std::cout << "special node = " << Object::special << "\n";
            ant = Object::special;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            Object::special = 0;
        }
        ObjectUpdateInfo updateInfo(&window);
        updateInfo.dt = dt;
        updateInfo.mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView());
        updateInfo.mouseWheelDelta = mouseWheelDelta;
        for (auto& object : objects){
            object->update(updateInfo);
        }
        if (Object::special && Object::special2) {
            Object::special2 = 0;
        }
        window.clear();
        std::vector<std::shared_ptr<GraphicsComponent>> graphicsComponents;
        for (const auto& object : objects){
            for (const auto& graphicsComponent : object->getComponentsOfTypeFromSubtree<GraphicsComponent>()){
                graphicsComponents.push_back(graphicsComponent);
            }
        }
        std::sort(graphicsComponents.begin(), graphicsComponents.end(), [&](const std::shared_ptr<GraphicsComponent>& a, const std::shared_ptr<GraphicsComponent>& b) { return a->getZIndex() > b->getZIndex(); });
        for (auto& graphicsComponent : graphicsComponents){
            graphicsComponent->beforeRender();
        }
        for (auto& graphicsComponent : graphicsComponents){
            graphicsComponent->draw(window, sf::RenderStates::Default);
        }
        window.display();
    }
    return 0;
}
// cache globalTransform
// setPosition, setOrigin
// RectTransform -> {sf::Transform (matrice)}
// sa fac json de la 0
// rename update
// node component -> copil doar node component
// node component -> (reper-ul sau transformul in general) pt mn: unde e cineva in raport cu parintele lui. transform: aabb, pt fiecare margine
// unde se afla fata de aabb-ul parintelui (procentual, duh)
// panel, un buton lipit de marginea din stanga la mijloc, plus altul, cu w&h relativ tot

/*
implement a c++ sfml class:

So, I want to implement a thing Transform which has:
setPosition, setOrigin, setScale, setAngle and I want to be able to combine two transforms
because I want to have a hierarchy of objects and I want to be able for a object to
setPosition, setOrigin relative to its parent and I want to be able to combine them so that I
could get the real world positions of things
*/