#pragma once

#include "Light.h"

class SpotLight : public Light{
private:
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;

public:
	SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float cutOff, LightAttenuation* attenuation);
	virtual ~SpotLight();

	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);

	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);

	float getCutOff();
	void setCutOff(float cutOff);
};