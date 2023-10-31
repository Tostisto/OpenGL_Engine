#pragma once

#include "Light.h"

class SpotLight : public Light{
private:
	glm::vec3 position;
	glm::vec3 direction;

public:
	SpotLight();
	SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color);
	virtual ~SpotLight();

	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);

	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);
};