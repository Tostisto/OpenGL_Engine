#include "Light.h"

Light::Light() {}

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
	Notify("light_color", &this->color);
}

glm::vec3 Light::getColor(glm::vec3 color)
{
	return color;
}

int Light::getLightType(LightType type)
{
	return type;
}

void Light::setLightIndex(int index)
{
	this->LightIndex = index;
}

int Light::getLightIndex()
{
	return this->LightIndex;
}
