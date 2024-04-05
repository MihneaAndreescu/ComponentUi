#include "Object.h"
#include "Component.h"
#include "ObjectUpdateInfo.h"
#include <cassert>

void Object::addComponent(std::shared_ptr<Component> component)
{
	m_components.push_back(component);
}

bool Object::eraseComponent(std::shared_ptr<Component> component)
{
	bool found = false;
	for (size_t i = 0; i < m_components.size(); i++)
	{
		if (m_components[i] == component)
		{
			found = true;
			swap(m_components[i], m_components.back());
			m_components.pop_back();
			i--;
		}
	}
	return found;
}

//template<std::derived_from<Component> DerivedType> std::shared_ptr<DerivedType> Object::getTheUniqueComponentOfType() const
//{
//	std::shared_ptr<DerivedType> componentOfType;
//	assert(!componentOfType); // delete later, useless
//	for (const auto& component : m_components) 
//	{ 
//		if(std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (component))
//		{
//			assert(!componentOfType);
//			componentOfType = castedComponent;
//		}
//	}
//	assert(componentOfType);
//	return componentOfType;
//}
//
//template<std::derived_from<Component> DerivedType> std::vector<std::shared_ptr<DerivedType>> Object::getComponentsOfType() const
//{
//	std::vector<std::shared_ptr<DerivedType>> componentsOfType;
//	for (size_t i = 0; i < m_components.size(); i++)
//	{
//		if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (m_components[i]))
//		{
//			componentsOfType.push_back(castedComponent);
//		}
//	}
//	return componentsOfType;
//}

void Object::update(ObjectUpdateInfo updateInfo)
{
}

void Object::clearComponents()
{
	m_components.clear();
}/*

#include "GraphicsComponent.h"
template std::vector<std::shared_ptr<GraphicsComponent>> Object::getComponentsOfType<GraphicsComponent>() const;
template std::shared_ptr<GraphicsComponent> Object::getTheUniqueComponentOfType<GraphicsComponent>() const;

#include "AABBObjectGraphicsComponent.h"
template std::vector<std::shared_ptr<AABBObjectGraphicsComponent>> Object::getComponentsOfType<AABBObjectGraphicsComponent>() const;
template std::shared_ptr<AABBObjectGraphicsComponent> Object::getTheUniqueComponentOfType<AABBObjectGraphicsComponent>() const;

#include "AABBButtonObjectGraphicsComponent.h"
template std::vector<std::shared_ptr<AABBButtonObjectGraphicsComponent>> Object::getComponentsOfType<AABBButtonObjectGraphicsComponent>() const;
template std::shared_ptr<AABBButtonObjectGraphicsComponent> Object::getTheUniqueComponentOfType<AABBButtonObjectGraphicsComponent>() const;

#include "ShapeComponent.h"
template std::vector<std::shared_ptr<ShapeComponent>> Object::getComponentsOfType<ShapeComponent>() const;
template std::shared_ptr<ShapeComponent> Object::getTheUniqueComponentOfType<ShapeComponent>() const;

#include "AABBShapeComponent.h"
template std::vector<std::shared_ptr<AABBShapeComponent>> Object::getComponentsOfType<AABBShapeComponent>() const;
template std::shared_ptr<AABBShapeComponent> Object::getTheUniqueComponentOfType<AABBShapeComponent>() const;
*/
