#include "Component.h"
#include <vector>
#include <memory>
#include "Object.h"

class NodeComponent : public Component 
{
private:
	std::vector<std::shared_ptr<NodeComponent>> m_components;
	std::shared_ptr<Object> m_object;
public:
	std::shared_ptr<Object> getObject() const override;
	void addComponent(std::shared_ptr<NodeComponent> component);
	bool eraseComponent(std::shared_ptr<NodeComponent> component);
	void clearComponents();
	std::vector<std::shared_ptr<NodeComponent>> getComponents() const;
	NodeComponent(std::shared_ptr<Object> object); 
};