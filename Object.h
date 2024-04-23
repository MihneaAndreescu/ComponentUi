#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <concepts>
#include <cassert>
#include "Component.h"

class ObjectUpdateInfo;
class Component;
class NodeComponent;

class Object : public std::enable_shared_from_this<Object>
{ 
private:
	std::vector<std::shared_ptr<Component>> m_childComponents;
protected:
	void addComponent(std::shared_ptr<Component> component);
	bool eraseComponent(std::shared_ptr<Component> component);
	void clearComponents();
	std::shared_ptr<Object> getSharedThis();
	sf::Vector2f intervalize(sf::Vector2f p, sf::Vector2f low, sf::Vector2f high) const
	{
		p.x = std::max(p.x, low.x);
		p.y = std::max(p.y, low.y);
		p.x = std::min(p.x, high.x);
		p.y = std::min(p.y, high.y);
		return p;
	}
public:
	virtual void create() = 0;
	virtual sf::Vector2f getLocalPosition() const = 0; 
	virtual sf::Vector2f getLocalSize() const = 0;
	std::pair<sf::Vector2f, sf::Vector2f> getGlobalPositionAndSize() const
	{
		std::shared_ptr<Object> parent = getParent();
		if (!parent)
		{
			return { getLocalPosition(), getLocalSize() };
		}
		auto [parentPosition, parentSize] = parent->getGlobalPositionAndSize();
		sf::Vector2f localPosition = getLocalPosition();
		sf::Vector2f localSize = getLocalSize();
		localPosition = intervalize(localPosition, sf::Vector2f(0, 0), sf::Vector2f(1, 1) - localSize);
		localSize = intervalize(localSize, sf::Vector2f(0, 0), sf::Vector2f(1, 1) - localSize);
		sf::Vector2f size = { parentSize.x * localSize.x, parentSize.y * localSize.y };
		sf::Vector2f position = parentPosition + sf::Vector2f(parentSize.x * localPosition.x, parentSize.y * localPosition.y);
		return { position, size };
	}
	friend class Component;
	std::shared_ptr<NodeComponent> getNodeComponent();
	std::vector<std::shared_ptr<Object>> getChildren() const;
	std::shared_ptr<Object> getParent() const;
	void addChild(std::shared_ptr<Object> object);
	bool eraseChild(std::shared_ptr<Object> object);
	void clearChildren();
	template<std::derived_from<Component> DerivedType> std::shared_ptr<DerivedType> getTheUniqueComponentOfType() const
	{
		std::shared_ptr<DerivedType> componentOfType;
		for (const auto& component : m_childComponents)
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
		for (size_t i = 0; i < m_childComponents.size(); i++)
		{
			if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (m_childComponents[i]))
			{
				componentsOfType.push_back(castedComponent);
			}
		}
		return componentsOfType;
	}
	template<std::derived_from<Component> DerivedType> void getComponentsOfTypeFromSubtreeRef(std::vector<std::shared_ptr<DerivedType>>& componentsOfType) const
	{
		for (size_t i = 0; i < m_childComponents.size(); i++)
		{
			if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (m_childComponents[i]))
			{
				componentsOfType.push_back(castedComponent);
			}
		}
		for (auto& child : getChildren())
		{
			child->getComponentsOfTypeFromSubtreeRef(componentsOfType);
		}
	}
	template<std::derived_from<Component> DerivedType> std::vector<std::shared_ptr<DerivedType>> getComponentsOfTypeFromSubtree() const
	{
		std::vector<std::shared_ptr<DerivedType>> componentsOfType;
		getComponentsOfTypeFromSubtreeRef(componentsOfType);
		return componentsOfType;
	}
	template<std::derived_from<Component> DerivedType> bool hasComponentsOfType() const
	{
		for (size_t i = 0; i < m_childComponents.size(); i++)
		{
			if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (m_childComponents[i]))
			{
				return true;
			}
		}
		return false;
	}
	virtual void updateVirtual(ObjectUpdateInfo updateInfo);
	void update(ObjectUpdateInfo updateInfo);
};


