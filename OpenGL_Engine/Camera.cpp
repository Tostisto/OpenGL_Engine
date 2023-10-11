#include "Camera.h"

Camera::Camera(){}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->camera_pos, this->camera_pos + this->camera_front, this->camera_up);
}

glm::vec3 Camera::GetCameraPosition()
{
	return this->camera_pos;
}

void Camera::CameraMovement(Window* window)
{
    const float cameraSpeed = 0.05f;
    glm::vec3 previousCameraPos = this->camera_pos; // Store the previous camera position

    if (window->GetKey(GLFW_KEY_W) == GLFW_PRESS)
    {
        this->camera_pos += cameraSpeed * this->camera_front;
    }

    if (window->GetKey(GLFW_KEY_S) == GLFW_PRESS) {
        this->camera_pos -= cameraSpeed * this->camera_front;
    }

    if (window->GetKey(GLFW_KEY_A) == GLFW_PRESS) {
        this->camera_pos -= glm::normalize(glm::cross(this->camera_front, this->camera_up)) * cameraSpeed;
    }

    if (window->GetKey(GLFW_KEY_D) == GLFW_PRESS) {
        this->camera_pos += glm::normalize(glm::cross(this->camera_front, this->camera_up)) * cameraSpeed;
    }

    if (window->GetKey(GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->camera_pos += cameraSpeed * this->camera_up;
    }

    if (window->GetKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        this->camera_pos -= cameraSpeed * this->camera_up;
    }

    // Compare the previous camera position with the new one
    if (this->camera_pos != previousCameraPos) {
        fprintf(stderr, "Camera Position: %f, %f, %f\n", this->camera_pos.x, this->camera_pos.y, this->camera_pos.z);
        Notify();
    }
}

void Camera::MouseMovement(float x_pos, float y_pos)
{
    float x_offset = x_pos - last_x;
    float y_offset = last_y - y_pos;
    last_x = x_pos;
    last_y = y_pos;

    float speed = 0.1f;
    x_offset *= speed;
    y_offset *= speed;

    yaw += x_offset;    // Increase y offset
    pitch += y_offset;  // Increase x offset

    glm::vec3 target;
    target.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    target.y = sin(glm::radians(pitch));
    target.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front = glm::normalize(target);

    Notify();
}

void Camera::Update(Subject* subject)
{
    double mouse_x, mouse_y;

    mouse_x = Callback::GetInstance()->GetMouseX();
    mouse_y = Callback::GetInstance()->GetMouseY();

    fprintf(stderr, "Mouse Position: %f, %f\n", mouse_x, mouse_y);

    MouseMovement(mouse_x, mouse_y);
}
