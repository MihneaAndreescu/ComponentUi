#pragma once

#include "Object.h"

enum class ButtonState { Idle = 0, Hover = 1, Active = 2, Cnt = 3 };

class ObjectUpdateInfo;

class ButtonObject : public Object
{
private:
	ButtonState m_buttonState;
public:
	ButtonObject();
	void update(ObjectUpdateInfo updateInfo) override;
	virtual void onIdle();
	virtual void onHover();
	virtual void onActive();
};
