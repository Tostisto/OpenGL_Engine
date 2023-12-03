#pragma once

#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Rotation : public Transformation
{
protected:
	float angle;
	glm::vec3 axis;
	float speed;

public:
	Rotation(float angle, glm::vec3 axis);
	Rotation(float angle, glm::vec3 axis, float speed);
	void transform(glm::mat4* matrix) override;
};