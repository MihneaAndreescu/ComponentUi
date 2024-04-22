#include "Object.h"
#include "Component.h"
#include "ObjectUpdateInfo.h"
#include "NodeComponent.h"	

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

#include <iostream>

void Object::updateVirtual(ObjectUpdateInfo updateInfo)
{
	std::cout << "from Object\n";
}

void Object::clearComponents()
{
	m_components.clear();
}

std::shared_ptr<NodeComponent> Object::getNodeComponent() 
{
	if (!hasComponentsOfType<NodeComponent>())
	{
		addComponent(std::make_shared<NodeComponent>(getSharedThis()));
	}
	return getTheUniqueComponentOfType<NodeComponent>();
}

void Object::addChild(std::shared_ptr<Object> object)
{
	getNodeComponent()->addComponent(object->getNodeComponent());
}

bool Object::eraseChild(std::shared_ptr<Object> object)
{
	return getNodeComponent()->eraseComponent(object->getNodeComponent());
}

void Object::clearChildren()
{
	getNodeComponent()->clearComponents();
}

std::shared_ptr<Object> Object::getSharedThis()
{
	return shared_from_this();
}

#include <iostream>

void Object::update(ObjectUpdateInfo updateInfo)
{
	std::cout << "this = " << this << "\n";
	updateVirtual(updateInfo);
	for (auto& component : getNodeComponent()->getComponents())
	{
		std::shared_ptr<Object> obj = component->getObject();
		std::cout << "going from " << this << " to " << obj << "\n";
		obj->update(updateInfo);
	}
}
