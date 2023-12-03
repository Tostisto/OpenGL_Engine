#include "Camera.h"

Camera::Camera()
{
	cameraSpotLight = new CameraSpotLight(
		this->camera_pos,
		this->camera_front,
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::cos(glm::radians(20.0f)),
		new LightAttenuation(1.0f, 0.0005f, 0.0005f)
	);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->camera_pos, this->camera_pos + this->camera_front, this->camera_up);
}

glm::vec3 Camera::GetCameraPos()
{
	return this->camera_pos;
}

glm::vec3 Camera::GetCameraDirection()
{
	return this->camera_front;
}

void Camera::MoveForward()
{
	this->camera_pos += cameraSpeed * this->camera_front;

	this->cameraSpotLight->setPosition(this->camera_pos);

	Notify(CAMERA_UPDATE, nullptr);
}

void Camera::MoveBackward()
{
	this->camera_pos -= cameraSpeed * this->camera_front;

	this->cameraSpotLight->setPosition(this->camera_pos);

	Notify(CAMERA_UPDATE, nullptr);

}

void Camera::MoveLeft()
{
	this->camera_pos -= glm::normalize(glm::cross(this->camera_front, this->camera_up)) * cameraSpeed;

	this->cameraSpotLight->setPosition(this->camera_pos);

	Notify(CAMERA_UPDATE, nullptr);
}

void Camera::MoveRight()
{
	this->camera_pos += glm::normalize(glm::cross(this->camera_front, this->camera_up)) * cameraSpeed;

	this->cameraSpotLight->setPosition(this->camera_pos);

	Notify(CAMERA_UPDATE, nullptr);
}

void Camera::MoveUp()
{
	this->camera_pos += cameraSpeed * this->camera_up;

	this->cameraSpotLight->setPosition(this->camera_pos);

	Notify(CAMERA_UPDATE, nullptr);
}

void Camera::MoveDown()
{
	this->camera_pos -= cameraSpeed * this->camera_up;

	this->cameraSpotLight->setPosition(this->camera_pos);

	Notify(CAMERA_UPDATE, nullptr);
}

void Camera::SetCameraSpeed(float speed)
{
	this->cameraSpeed = speed;
}

void Camera::SetMouseSensitivity(float sensitivity)
{
	this->mouseSensitivity = sensitivity;
}

float Camera::GetPitch()
{
	return this->pitch;
}

float Camera::GetYaw()
{
	return this->yaw;
}

void Camera::CameraSpotLightControll()
{
	if (cameraSpotLight->isEnabled())
	{
		cameraSpotLight->setEnabled(false);
	}
	else
	{
		cameraSpotLight->setEnabled(true);
	}

	Notify(CAMERA_UPDATE, nullptr);
}

CameraSpotLight* Camera::GetCameraSpotLight()
{
	return this->cameraSpotLight;
}

glm::vec2 Camera::ApplyMouseSensitivity(glm::vec2 angles)
{
	angles *= this->mouseSensitivity;
	return angles;
}

void Camera::UpdateCameraOrientation(glm::vec2 angles)
{
	yaw += angles.x;
	pitch += angles.y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	UpdateCameraFront();
}

void Camera::UpdateCameraFront()
{
	glm::vec3 target;
	target.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	target.y = sin(glm::radians(pitch));
	target.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	camera_front = glm::normalize(target);

	this->cameraSpotLight->setDirection(this->camera_front);

	Notify(CAMERA_UPDATE, nullptr);
}