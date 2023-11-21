#pragma once

#include "SpotLight.h"

class CameraSpotLight : public SpotLight
{
private:
	bool enabled;

public:
	CameraSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float cutOff, LightAttenuation* attenuation);
	virtual ~CameraSpotLight();

	bool isEnabled();
	void setEnabled(bool enabled);	
};

