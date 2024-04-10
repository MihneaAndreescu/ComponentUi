#pragma once
#include <memory>
#include "Object.h"

class Object;

class Component
{
protected:
	virtual std::shared_ptr<Object> getObject() const = 0;
public:
	virtual ~Component() = default;
	friend class Object;
};