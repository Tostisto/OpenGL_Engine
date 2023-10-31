#include "SpotLight.h"

SpotLight::SpotLight()
{
}

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color)
{
	this->setPosition(position);
	this->setDirection(direction);
	this->setColor(color);
	this->setLightType(LightType::SPOT_LIGHT);
}

SpotLight::~SpotLight()
{
}

glm::vec3 SpotLight::getPosition()
{
	return this->position;
}

void SpotLight::setPosition(glm::vec3 position)
{
	this->position = position;
	Notify("light_position", &this->position);
}

glm::vec3 SpotLight::getDirection()
{
	return this->direction;
}

void SpotLight::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}