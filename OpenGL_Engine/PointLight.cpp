#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 color, LightAttenuation* attenuation) : Light(color, attenuation)
{
	this->setLightType(LightType::POINT_LIGHT);
	this->setPosition(position);
}	

PointLight::~PointLight() {}

glm::vec3 PointLight::getPosition()
{
	return this->position;
}

void PointLight::setPosition(glm::vec3 position)
{
	this->position = position;
	Notify(LIGHT_UPDATE, nullptr);
}