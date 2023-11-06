#include "Rotation.h"

Rotation::Rotation(float angle, glm::vec3 axis)
{
	this->angle = angle;
	this->axis = axis;
	this->speed = 0.0f;
}

Rotation::Rotation(float angle, glm::vec3 axis, float speed)
{
   	this->angle = angle;
	this->axis = axis;
	this->speed = speed;
}

void Rotation::transform(glm::mat4* matrix)
{
	this->angle += this->speed;
	*matrix = glm::rotate(*matrix, this->angle, this->axis);
}