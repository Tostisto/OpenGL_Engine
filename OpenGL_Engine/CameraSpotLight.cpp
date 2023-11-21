#include "CameraSpotLight.h"

CameraSpotLight::CameraSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float cutOff)
{
	this->setPosition(position);
	this->setColor(color);
	this->setDirection(direction);
	this->setCutOff(cutOff);
	this->enabled = true;
	this->setAttenuation(new LightAttenuation(1.0f, 0.1f, 0.01f));
}

CameraSpotLight::~CameraSpotLight()
{
}

bool CameraSpotLight::isEnabled()
{
	return this->enabled;
}

void CameraSpotLight::setEnabled(bool enabled)
{
	this->enabled = enabled;
}
