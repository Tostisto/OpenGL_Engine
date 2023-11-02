#include "PointLight.h"

PointLight::PointLight() {
	this->setLightType(LightType::POINT_LIGHT);
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color)
{
	this->setLightType(LightType::POINT_LIGHT);
	this->setPosition(position);
	this->setColor(color);
}	

PointLight::~PointLight() {}

glm::vec3 PointLight::getPosition()
{
	return this->position;
}

void PointLight::setPosition(glm::vec3 position)
{
	this->position = position;
	Notify("light", nullptr);
}