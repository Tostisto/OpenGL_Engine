#include "Scale.h"

Scale::Scale(glm::vec3 scale) {
	this->scale = scale;
}

Scale::Scale(float scale)
{
	this->scale = glm::vec3(scale);
}

void Scale::transform(glm::mat4* matrix) {
	*matrix = glm::scale(*matrix, scale);
}