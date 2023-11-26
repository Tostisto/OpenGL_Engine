#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float cutOff, LightAttenuation* attenuation) : Light(color, attenuation)
{
	this->setPosition(position);
	this->setDirection(direction);
	this->setLightType(LightType::SPOT_LIGHT);
	this->setCutOff(cutOff);
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
	Notify(LIGHT_UPDATE, nullptr);
}

glm::vec3 SpotLight::getDirection()
{
	return this->direction;
}

void SpotLight::setDirection(glm::vec3 direction)
{
	this->direction = direction;
	Notify(LIGHT_UPDATE, nullptr);
}

float SpotLight::getCutOff()
{
	return this->cutOff;
}

void SpotLight::setCutOff(float cutOff)
{
	this->cutOff = cutOff;
	Notify(LIGHT_UPDATE, nullptr);
}
