#include "CleanTransformations.h"

CleanTransformations::CleanTransformations(glm::mat4 matrix)
{
	this->matrix = matrix;
}

glm::mat4 CleanTransformations::getMatrix()
{
	return matrix;
}
