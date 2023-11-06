#include "Translation.h"

Translation::Translation(glm::vec3 translation)
{
	this->translation = translation;
}

void Translation::transform(glm::mat4* matrix)
{
	*matrix = glm::translate(*matrix, translation);
}
