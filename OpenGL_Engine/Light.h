#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Subject.h"

class Light : public Subject
{
private:
	glm::vec3 position;
	glm::vec3 color;

public:
	Light();
	~Light();

	glm::vec3 getPosition();
	glm::vec3 getColor();

	void setPosition(glm::vec3 position);
	void setColor(glm::vec3 color);
};