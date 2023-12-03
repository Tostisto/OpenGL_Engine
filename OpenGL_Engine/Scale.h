#pragma once

#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Scale : public Transformation
{
private:
	glm::vec3 scale;

public:
	Scale(glm::vec3 scale);
	Scale(float scale);


	void transform(glm::mat4* matrix) override;
};