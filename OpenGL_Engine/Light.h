#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Subject.h"

#include "LightAttenuation.h"
#include "LightType.h"

class Light : public Subject
{
private:
	glm::vec3 color;
	LightType type = LightType::NONE;
	int LightIndex;

	LightAttenuation* attenuation;

protected:
	void setLightType(LightType type);
	void setColor(glm::vec3 color);
	glm::vec3 getColor(glm::vec3 color);
	int getLightType(LightType type);

public:
	Light();
	virtual ~Light();

	glm::vec3 getColor();
	int getLightType();

	void setLightIndex(int index);
	int getLightIndex();
	
	LightAttenuation* getAttenuation();
	void setAttenuation(LightAttenuation* attenuation);
};