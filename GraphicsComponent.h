#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class GraphicsComponent : public Component
{
private:
	int m_zIndex;
public:
	GraphicsComponent() : m_zIndex(0)
	{

	}
	virtual ~GraphicsComponent() = default;
	virtual void beforeRender();
	virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const = 0;

	int getZIndex() const;
	void setZIndex(int zIndex);
};
