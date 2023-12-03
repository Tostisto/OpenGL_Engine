#include "CameraSpotLight.h"

CameraSpotLight::CameraSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float cutOff, LightAttenuation* attenuation) : SpotLight(position, direction, color, cutOff, attenuation)
{
	this->enabled = false;
}

CameraSpotLight::~CameraSpotLight() {}

bool CameraSpotLight::isEnabled()
{
	return this->enabled;
}

void CameraSpotLight::setEnabled(bool enabled)
{
	this->enabled = enabled;
}
