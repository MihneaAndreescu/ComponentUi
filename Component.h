#pragma once
#include <memory>

class Object;

class Component
{
protected:
	virtual std::shared_ptr<Object> getObject() const = 0;

public:
	virtual ~Component() = default;
};