#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class GraphicsComponent : public Component
{
public:
	virtual ~GraphicsComponent() = default;
	virtual void beforeRender();
	virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const = 0;
};