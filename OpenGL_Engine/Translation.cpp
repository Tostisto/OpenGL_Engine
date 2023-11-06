#include "Translation.h"

Translation::Translation(glm::vec3 translation) : translation(translation) {}

glm::mat4 Translation::getMatrix()
{
	return glm::translate(glm::mat4(1.0f), translation);
}