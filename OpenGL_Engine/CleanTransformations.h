#pragma once

#include <glm/glm.hpp>
#include "Transformation.h"

class CleanTransformations : public Transformation
{
private:
	glm::mat4 matrix;

public:
	CleanTransformations(glm::mat4 matrix);
	glm::mat4 getMatrix() override;
};

