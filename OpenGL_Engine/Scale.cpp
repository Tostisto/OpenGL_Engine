#include "Scale.h"

Scale::Scale(glm::vec3 scale) : scale(scale) {}

glm::mat4 Scale::getMatrix() const
{
	return glm::scale(glm::mat4(1.0f), scale);
}