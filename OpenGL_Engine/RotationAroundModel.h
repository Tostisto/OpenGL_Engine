#pragma once

#include "Transformation.h"
#include "Drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class RotationAroundModel : public Transformation
{
private:
	float angle;
	float distance;
	glm::vec3 axis;
	glm::mat4 modelMatrix;
	Drawable* centerModel;

public:
	RotationAroundModel(float angle, float relativePos, glm::vec3 axis, glm::mat4 modelMatrix, Drawable* centerModel);
	glm::mat4 getMatrix() override;

	void GetDistanceInGlobal();
};

