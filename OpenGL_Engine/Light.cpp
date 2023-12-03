#include "Light.h"

Light::Light(glm::vec3 color)
{
	this->setColor(color);
}

Light::Light(glm::vec3 color, LightAttenuation* attenuation)
{
	this->setColor(color);
	this->setAttenuation(attenuation);
}

Light::~Light() {}

glm::vec3 Light::getColor()
{
	return this->color;
}

int Light::getLightType()
{
	return static_cast<int>(this->type);
}

void Light::setLightType(LightType type)
{
	this->type = type;
}

void Light::setColor(glm::vec3 color)
{
	this->color = color;
	Notify(LIGHT_UPDATE, nullptr);
}

glm::vec3 Light::getColor(glm::vec3 color)
{
	return color;
}

int Light::getLightType(LightType type)
{
	return type;
}

LightAttenuation* Light::getAttenuation()
{
	return this->attenuation;
}

void Light::setAttenuation(LightAttenuation* attenuation)
{
	this->attenuation = attenuation;
}

void Light::setLightIndex(int index)
{
	this->LightIndex = index;
	Notify(LIGHT_UPDATE, nullptr);
}

int Light::getLightIndex()
{
	return this->LightIndex;
}