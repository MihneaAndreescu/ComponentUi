#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <concepts>
#include <cassert>
#include "Component.h"
#include "MyTransform.h"

class ObjectUpdateInfo;
class Component;
class NodeComponent;

class Object : public std::enable_shared_from_this<Object> {
private:
	std::vector<std::shared_ptr<Component>> m_childComponents;
protected:
	MyTransform m_transform;
	void addComponent(std::shared_ptr<Component> component);
	bool eraseComponent(std::shared_ptr<Component> component);
	void clearComponents();
	std::shared_ptr<Object> getSharedThis();
public:
	std::shared_ptr<sf::Vector2f> restpos;
	std::shared_ptr<sf::Vector2f> restdim;
	sf::FloatRect getBoundingBox() {
		return m_transform.getBoundingBox();
	}
	virtual void create() = 0;

	void setPosition(sf::Vector2f newPosition);
	void setOrigin(sf::Vector2f newOrigin);
	void setScale(sf::Vector2f newScale);
	sf::Vector2f getPosition() const;
	sf::Vector2f getScale() const;
	sf::Vector2f getOrigin() const;

	MyTransform getGlobalTransform() const {
		std::shared_ptr<Object> parent = getParent(); 
		if (!parent) {
			return m_transform; 
		}
		MyTransform parentTransform = parent->getGlobalTransform(); 
		return m_transform.combine(parentTransform);
	}
	friend class Component;
	std::shared_ptr<NodeComponent> getNodeComponent();
	std::vector<std::shared_ptr<Object>> getChildren() const;
	std::shared_ptr<Object> getParent() const;
	void addChild(std::shared_ptr<Object> object);
	bool eraseChild(std::shared_ptr<Object> object);
	void clearChildren();
	template<std::derived_from<Component> DerivedType> std::shared_ptr<DerivedType> getTheUniqueComponentOfType() const{
		std::shared_ptr<DerivedType> componentOfType;
		for (const auto& component : m_childComponents){
			if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (component)){
				assert(!componentOfType);
				componentOfType = castedComponent;
			}
		}
		assert(componentOfType);
		return componentOfType;
	}
	template<std::derived_from<Component> DerivedType> std::vector<std::shared_ptr<DerivedType>> getComponentsOfType() const{
		std::vector<std::shared_ptr<DerivedType>> componentsOfType;
		for (size_t i = 0; i < m_childComponents.size(); i++){
			if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (m_childComponents[i])){
				componentsOfType.push_back(castedComponent);
			}
		}
		return componentsOfType;
	}
	template<std::derived_from<Component> DerivedType> void getComponentsOfTypeFromSubtreeRef(std::vector<std::shared_ptr<DerivedType>>& componentsOfType) const{
		for (size_t i = 0; i < m_childComponents.size(); i++){
			if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (m_childComponents[i])){
				componentsOfType.push_back(castedComponent);
			}
		}
		for (auto& child : getChildren()){
			child->getComponentsOfTypeFromSubtreeRef(componentsOfType);
		}
	}
	template<std::derived_from<Component> DerivedType> std::vector<std::shared_ptr<DerivedType>> getComponentsOfTypeFromSubtree() const{
		std::vector<std::shared_ptr<DerivedType>> componentsOfType;
		getComponentsOfTypeFromSubtreeRef(componentsOfType);
		return componentsOfType;
	}
	template<std::derived_from<Component> DerivedType> bool hasComponentsOfType() const{
		for (size_t i = 0; i < m_childComponents.size(); i++){
			if (std::shared_ptr<DerivedType> castedComponent = std::dynamic_pointer_cast<DerivedType> (m_childComponents[i])){
				return true;
			}
		}
		return false;
	}
	virtual void updateVirtual(ObjectUpdateInfo updateInfo);
	void update(ObjectUpdateInfo updateInfo);
	static std::shared_ptr<Object> special;
	static std::shared_ptr<Object> special2;
};

