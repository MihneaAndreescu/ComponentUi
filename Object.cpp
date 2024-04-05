#include "Object.h"
#include "Component.h"
#include "ObjectUpdateInfo.h"

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

void Object::update(ObjectUpdateInfo updateInfo)
{
}

void Object::clearComponents()
{
	m_components.clear();
}