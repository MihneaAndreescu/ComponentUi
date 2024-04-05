#include "ButtonObject.h"
#include "ObjectUpdateInfo.h"
#include "ShapeComponent.h"

ButtonObject::ButtonObject() :
	m_buttonState(ButtonState::Idle)
{
}

void ButtonObject::update(ObjectUpdateInfo updateInfo)
{
	Object::update(updateInfo);
	m_buttonState = ButtonState::Idle;
	bool inside = false;
	for (const auto& component : getComponentsOfType<ShapeComponent>())
	{
		if (component->contains(updateInfo.mousePosition))
		{
			inside = true;
		}
	}
	if (inside)
	{
		m_buttonState = ButtonState::Hover;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_buttonState = ButtonState::Active;
		}
	}
	if (m_buttonState == ButtonState::Idle)
	{
		onIdle();
	}
	if (m_buttonState == ButtonState::Hover)
	{
		onHover();
	}
	if (m_buttonState == ButtonState::Active)
	{
		onActive();
	}
}

void ButtonObject::onIdle()
{
}

void ButtonObject::onHover()
{
}

void ButtonObject::onActive()
{
}

