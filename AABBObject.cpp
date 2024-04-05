//#include "AABBObject.h"
//#include "AABBObjectGraphicsComponent.h"
//
//const sf::Vector2f& AABBObject::getSize() const
//{
//	return m_size;
//}
//
//const sf::Vector2f& AABBObject::getCenter() const
//{
//	return m_center;
//}
//
//void AABBObject::setSize(sf::Vector2f newSize)
//{
//	m_size = newSize;
//}
//
//void AABBObject::setCenter(sf::Vector2f newCenter)
//{
//	m_center = newCenter;
//}
//
//AABBObject::AABBObject()
//{
//	addComponent(std::make_shared<AABBObjectGraphicsComponent>(m_center, m_size));
//}
//
//void AABBObject::setTexture(std::shared_ptr<sf::Texture> newTexture)
//{
//	for (auto& component : getComponentsOfType2<AABBObjectGraphicsComponent>())
//	{
//		component->setTexture(newTexture);
//	}
//}
