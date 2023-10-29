#include "Light.h"

Light::Light() {}

Light::~Light() {}

glm::vec3 Light::getPosition()
{
	return this->position;
}

glm::vec3 Light::getColor()
{
	return this->color;
}

void Light::setPosition(glm::vec3 position)
{
	this->position = position;
	Notify("light_position", &this->position);
}

void Light::setColor(glm::vec3 color)
{
	this->color = color;
	Notify("light_color", &this->color);
}