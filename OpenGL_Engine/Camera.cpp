#include "Camera.h"

Camera::Camera() {}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->camera_pos, this->camera_pos + this->camera_front, this->camera_up);
}

glm::vec3 Camera::GetCameraPos()
{
    return this->camera_pos;
}

void Camera::MoveForward()
{
    this->camera_pos += cameraSpeed * this->camera_front;
    Notify("camera", nullptr);
}

void Camera::MoveBackward()
{
    this->camera_pos -= cameraSpeed * this->camera_front;
    Notify("camera", nullptr);
}

void Camera::MoveLeft()
{
    this->camera_pos -= glm::normalize(glm::cross(this->camera_front, this->camera_up)) * cameraSpeed;
    Notify("camera", nullptr);
}

void Camera::MoveRight()
{
    this->camera_pos += glm::normalize(glm::cross(this->camera_front, this->camera_up)) * cameraSpeed;
    Notify("camera", nullptr);
}

void Camera::MoveUp()
{
    this->camera_pos += cameraSpeed * this->camera_up;
    Notify("camera", nullptr);
}

void Camera::MoveDown()
{
    this->camera_pos -= cameraSpeed * this->camera_up;
    Notify("camera", nullptr);
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

    Notify("camera", nullptr);
}