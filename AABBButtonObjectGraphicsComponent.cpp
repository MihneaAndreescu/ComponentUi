#include "AABBButtonObjectGraphicsComponent.h"
#include "AABBButtonObject.h"
#include "AABBShapeComponent.h"

sf::Glsl::Vec4 getVec4(sf::Color color)
{
	float red = color.r / 255.f;
	float green = color.g / 255.f;
	float blue = color.b / 255.f;
	float alpha = color.a / 255.f;
	return sf::Glsl::Vec4(red, green, blue, alpha);
}

std::shared_ptr<Object> AABBButtonObjectGraphicsComponent::getObject() const 
{
	return m_object;
}

sf::Vector2f AABBButtonObjectGraphicsComponent::getSize() const
{
	const auto shapeComponent = m_object->getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getSize();
}

sf::Vector2f AABBButtonObjectGraphicsComponent::getCenter() const
{
	const auto shapeComponent = m_object->getTheUniqueComponentOfType<AABBShapeComponent>();
	return shapeComponent->getCenter();
}

AABBButtonObjectGraphicsComponent::AABBButtonObjectGraphicsComponent(std::shared_ptr<AABBButtonObject> object) :
	m_object(object)
{
	if (!m_shader.loadFromFile("shader.frag", sf::Shader::Fragment))
	{
		exit(0);
	}
	m_shader.setUniform("texture", sf::Shader::CurrentTexture);
}

void AABBButtonObjectGraphicsComponent::onIdle()
{
	m_shader.setUniform("inputColor", getVec4(sf::Color::Green));
}

void AABBButtonObjectGraphicsComponent::onHover()
{
	m_shader.setUniform("inputColor", getVec4(sf::Color::Yellow));
}

void AABBButtonObjectGraphicsComponent::onActive()
{
	m_shader.setUniform("inputColor", getVec4(sf::Color::Red));
}

void AABBButtonObjectGraphicsComponent::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	renderStates.shader = &m_shader;
	AABBObjectGraphicsComponent::draw(renderTarget, renderStates);
}