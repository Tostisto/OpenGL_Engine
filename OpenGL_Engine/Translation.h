#pragma once

#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Translation : public Transformation
{
private:
	glm::vec3 translation;

public:
	Translation(glm::vec3 translation);
	void transform(glm::mat4* matrix) override;
};