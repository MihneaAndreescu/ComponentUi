#pragma once
#include <vector>
#include <memory>
#include <concepts>
#include <cassert>
#include "Component.h"

class ObjectUpdateInfo;
class Component;
class NodeComponent;

class Object
{
private:
	std::vector<std::shared_ptr<Component>> m_components;
protected:
	void addComponent(std::shared_ptr<Component> component);
	bool eraseComponent(std::shared_ptr<Component> component);
	void clearComponents();
public:
	friend class Component;
	std::shared_ptr<NodeComponent> getNodeComponent();
	void addChild(std::shared_ptr<Object> object);
	bool eraseChild(std::shared_ptr<Object> object);
	void clearChildren();
	template<std::derived_from<Component> DerivedType> std::shared_ptr<DerivedType> getTheUniqueComponentOfType() const
	{
		std::shared_ptr<DerivedType> componentOfType;
		for (const auto& component : m_components)
		{
			if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (component))
			{
				assert(!componentOfType);
				componentOfType = castedComponent;
			}
		}
		assert(componentOfType);
		return componentOfType;
	}
	template<std::derived_from<Component> DerivedType> std::vector<std::shared_ptr<DerivedType>> getComponentsOfType() const
	{
		std::vector<std::shared_ptr<DerivedType>> componentsOfType;
		for (size_t i = 0; i < m_components.size(); i++)
		{
			if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (m_components[i]))
			{
				componentsOfType.push_back(castedComponent);
			}
		}
		return componentsOfType;
	}
	template<std::derived_from<Component> DerivedType> bool hasComponentsOfType() const
	{
		for (size_t i = 0; i < m_components.size(); i++)
		{
			if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (m_components[i]))
			{
				return true;
			}
		}
		return false;
	}
public:
	virtual void updateVirtual(ObjectUpdateInfo updateInfo);
	void update(ObjectUpdateInfo updateInfo);
};


