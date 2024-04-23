#include "NodeComponent.h"
#include "ObjectUpdateInfo.h"

void NodeComponent::addComponent(std::shared_ptr<NodeComponent> component)
{
	assert(!component->m_parentComponent);
	component->m_parentComponent = std::dynamic_pointer_cast<NodeComponent>(getSharedThis());
	m_childComponents.push_back(component);
}

bool NodeComponent::eraseComponent(std::shared_ptr<NodeComponent> component)
{
	bool found = false;
	for (size_t i = 0; i < m_childComponents.size(); i++)
	{
		if (m_childComponents[i] == component)
		{
			found = true;
			m_childComponents[i]->m_parentComponent = 0;
			swap(m_childComponents[i], m_childComponents.back());
			m_childComponents.pop_back();
			i--;
		}
	}
	return found;
}

void NodeComponent::clearComponents()
{
	m_childComponents.clear();
}

std::shared_ptr<Object> NodeComponent::getObject() const
{
	return m_object;
}

NodeComponent::NodeComponent(std::shared_ptr<Object> object) :
	m_object(object)
{

}

std::vector<std::shared_ptr<NodeComponent>> NodeComponent::getComponents() const
{
	return m_childComponents;
}