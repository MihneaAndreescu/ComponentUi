#include "NodeComponent.h"
#include "ObjectUpdateInfo.h"

void NodeComponent::addComponent(std::shared_ptr<Component> component)
{
	m_components.push_back(component);
}

bool NodeComponent::eraseComponent(std::shared_ptr<Component> component)
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

void NodeComponent::clearComponents()
{
	m_components.clear();
}

std::shared_ptr<Object> NodeComponent::getObject() const
{
	return m_object;
}

NodeComponent::NodeComponent(std::shared_ptr<Object> object) :
	m_object(object)
{

}
	
std::vector<std::shared_ptr<Component>> NodeComponent::getComponents() const 
{
	return m_components;
}