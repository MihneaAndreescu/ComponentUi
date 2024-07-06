#include "Object.h"
#include "Component.h"
#include "ObjectUpdateInfo.h"
#include "NodeComponent.h"

#include <iostream>

void Object::setPosition(sf::Vector2f newPosition) {
	m_transform.setPosition(newPosition);
}

void Object::setOrigin(sf::Vector2f newOrigin) {
	m_transform.setOrigin(newOrigin);
}

void Object::setScale(sf::Vector2f newScale) {
	m_transform.setScale(newScale);
}

sf::Vector2f Object::getPosition() const {
	return m_transform.getPosition();
}

sf::Vector2f Object::getScale() const {
	return m_transform.getScale();
}

sf::Vector2f Object::getOrigin() const {
	return m_transform.getOrigin();
}

void Object::addComponent(std::shared_ptr<Component> component) {
	m_childComponents.push_back(component);
}

bool Object::eraseComponent(std::shared_ptr<Component> component) {
	bool found = false;
	for (size_t i = 0; i < m_childComponents.size(); i++) {
		if (m_childComponents[i] == component) {
			found = true;
			swap(m_childComponents[i], m_childComponents.back());
			m_childComponents.pop_back();
			i--;
		}
	}
	return found;
}

std::shared_ptr<Object> Object::getParent() const {
	if (!hasComponentsOfType<NodeComponent>()) {
		return 0;
	}
	std::shared_ptr<NodeComponent> parent = getTheUniqueComponentOfType<NodeComponent>()->getParentComponent();
	if (!parent) {
		return 0;
	}
	return parent->getObject();
}

void Object::updateVirtual(ObjectUpdateInfo updateInfo) {
}

void Object::clearComponents() {
	m_childComponents.clear();
}

std::vector<std::shared_ptr<Object>> Object::getChildren() const {
	std::vector<std::shared_ptr<Object>> children;
	if (hasComponentsOfType<NodeComponent>()) {
		for (auto& component : getTheUniqueComponentOfType<NodeComponent>()->getComponents()) {
			children.push_back(component->getObject());
		}
	}
	return children;
}

std::shared_ptr<NodeComponent> Object::getNodeComponent() {
	if (!hasComponentsOfType<NodeComponent>()) {
		addComponent(std::make_shared<NodeComponent>(getSharedThis()));
	}
	return getTheUniqueComponentOfType<NodeComponent>();
}

void Object::addChild(std::shared_ptr<Object> object) {
	getNodeComponent()->addComponent(object->getNodeComponent());
}

bool Object::eraseChild(std::shared_ptr<Object> object) {
	return getNodeComponent()->eraseComponent(object->getNodeComponent());
}

void Object::clearChildren() {
	getNodeComponent()->clearComponents();
}

std::shared_ptr<Object> Object::getSharedThis() {
	return shared_from_this();
}

void Object::update(ObjectUpdateInfo updateInfo) {
	updateVirtual(updateInfo);
	for (auto& component : getNodeComponent()->getComponents()){
		std::shared_ptr<Object> obj = component->getObject();
		obj->update(updateInfo);
	}
}

std::shared_ptr<Object> Object::special = 0;
std::shared_ptr<Object> Object::special2 = 0;
