#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
private:
	glm::vec3 direction;

public:
	DirectionalLight(glm::vec3 direction, glm::vec3 color);
	virtual ~DirectionalLight();

	glm::vec3 getDirection();	
	void setDirection(glm::vec3 direction);
};