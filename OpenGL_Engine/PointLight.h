#pragma once

#include "Light.h"

class PointLight : public Light
{
private:
	glm::vec3 position;

public:
	PointLight(glm::vec3 position, glm::vec3 color, LightAttenuation* attenuation);
	virtual ~PointLight();

	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
};

