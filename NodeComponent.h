#include "Component.h"
#include <vector>
#include <memory>
#include "Object.h"

class NodeComponent : public Component 
{
private:
	std::vector<std::shared_ptr<Component>> m_components;
	std::shared_ptr<Object> m_object;
protected:
	std::shared_ptr<Object> getObject() const override;
public:
	void addComponent(std::shared_ptr<Component> component);
	bool eraseComponent(std::shared_ptr<Component> component);
	void clearComponents();
	std::vector<std::shared_ptr<Component>> getComponents() const;

public:
	NodeComponent(std::shared_ptr<Object> object); 
};