#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class ObjectUpdateInfo;

class AABBPanelObject : public Object {
private:
	bool m_isDragging = false;
	bool m_isDragging2 = false;
	sf::Vector2f mouseOffset;
	sf::Vector2f mouseOffset2;
	sf::Vector2f dif;
public:
	AABBPanelObject();
	void updateVirtual(ObjectUpdateInfo updateInfo) override;
	void setSize(sf::Vector2f newSize);
	void create() override;
};
