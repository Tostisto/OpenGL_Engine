#include "PointLight.h"

PointLight::PointLight() {
	this->setLightType(LightType::POINT_LIGHT);
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, LightAttenuation* attenuation)
{
	this->setLightType(LightType::POINT_LIGHT);
	this->setPosition(position);
	this->setColor(color);
	this->setAttenuation(attenuation);
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