#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {
	this->setLightType(LightType::DIRECTIONAL_LIGHT);
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color)
{
	this->setLightType(LightType::DIRECTIONAL_LIGHT);
	this->setColor(color);
	this->setDirection(direction);
}

DirectionalLight::~DirectionalLight() {}

glm::vec3 DirectionalLight::getDirection()
{
	return this->direction;
}

void DirectionalLight::setDirection(glm::vec3 direction)
{
	this->direction = direction;
	Notify("light_direction", &this->direction);
}
