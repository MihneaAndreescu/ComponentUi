#include "GraphicsComponent.h"

void GraphicsComponent::beforeRender()
{
}

int GraphicsComponent::getZIndex() const
{
	return m_zIndex;
}

void GraphicsComponent::setZIndex(int zIndex)
{
	m_zIndex = zIndex;
}