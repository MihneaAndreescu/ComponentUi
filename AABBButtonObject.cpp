#include "AABBButtonObject.h"
#include "AABBShapeComponent.h"
#include "AABBButtonObjectGraphicsComponent.h"
#include "ObjectUpdateInfo.h"

AABBButtonObject::AABBButtonObject()
{

}

void AABBButtonObject::create()
{
	addComponent(std::make_shared<AABBShapeComponent>(getSharedThis()));
	addComponent(std::make_shared<AABBButtonObjectGraphicsComponent>(std::dynamic_pointer_cast<AABBButtonObject>(getSharedThis())));
}

void AABBButtonObject::onIdle()
{
	getTheUniqueComponentOfType<AABBButtonObjectGraphicsComponent>()->onIdle();
}

void AABBButtonObject::onHover()
{
	getTheUniqueComponentOfType<AABBButtonObjectGraphicsComponent>()->onHover();
}

void AABBButtonObject::onActive()
{
	getTheUniqueComponentOfType<AABBButtonObjectGraphicsComponent>()->onActive();
}

void AABBButtonObject::setTexture(std::shared_ptr<sf::Texture> newTexture)
{
	const auto graphicsComponent = getTheUniqueComponentOfType<AABBButtonObjectGraphicsComponent>();
	graphicsComponent->setTexture(newTexture);
}

void AABBButtonObject::setSize(sf::Vector2f newSize)
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	shapeComponent->setSize(newSize);
}

void AABBButtonObject::setPosition(sf::Vector2f newPosition)
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	shapeComponent->setPosition(newPosition);
}

void AABBButtonObject::setOrigin(sf::Vector2f newOrigin)
{
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	shapeComponent->setOrigin(newOrigin);
}

void AABBButtonObject::updateVirtual(ObjectUpdateInfo info)
{
	ButtonObject::updateVirtual(info);
	const auto shapeComponent = getTheUniqueComponentOfType<AABBShapeComponent>();
	sf::Vector2f position = shapeComponent->getPosition();
	position += (sf::Vector2f(0, -1) * 1.0f * info.dt) * ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * 1.0f);
	position += sf::Vector2f(0, 1) * 1.0f * info.dt * ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) * 1.0f);
	position += sf::Vector2f(-1, 0) * 1.0f * info.dt * ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) * 1.0f);
	position += sf::Vector2f(+1, 0) * 1.0f * info.dt * ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * 1.0f);

	shapeComponent->setPosition(position);

	sf::Vector2f size = shapeComponent->getSize();
	float m_scale = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_scale *= pow(2.0f, info.dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_scale *= pow(1.0f / 2.0f, info.dt);
	}
	size.x *= m_scale;
	size.y *= m_scale;
	shapeComponent->setSize(size);
}
