#pragma once
#include <memory>
#include "Object.h"

class Object;

class Component : public std::enable_shared_from_this<Component>
{
protected:
	virtual std::shared_ptr<Object> getObject() const = 0;
public:
	std::shared_ptr<Component> getSharedThis()
	{
		return shared_from_this();
	}
	virtual ~Component() = default;
	friend class Object;
};