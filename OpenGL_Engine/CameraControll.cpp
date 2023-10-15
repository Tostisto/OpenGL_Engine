#include "CameraControll.h"

CameraControll::CameraControll(Camera* camera, Window* window)
{
	this->camera = camera;
	this->window = window;
}

void CameraControll::MouseMovement(float x_pos, float y_pos)
{
    glfwSetCursorPos(this->window->window, this->window->width / 2, this->window->height / 2);

    glfwSetInputMode(this->window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float yawChange = this->window->width / 2 - x_pos;
    float pitchChange = this->window->height / 2 - y_pos;

    glm::vec2 angles = glm::vec2(yawChange, pitchChange);

    angles = this->camera->ApplyMouseSensitivity(angles);

    this->camera->UpdateCameraOrientation(angles);
}

void CameraControll::KeyboardMovement()
{
    if (window->GetKey(GLFW_KEY_W) == GLFW_PRESS)
    {
        this->camera->MoveForward();
    }

    if (window->GetKey(GLFW_KEY_S) == GLFW_PRESS) {
        this->camera->MoveBackward();
    }

    if (window->GetKey(GLFW_KEY_A) == GLFW_PRESS) {
        this->camera->MoveLeft();
    }

    if (window->GetKey(GLFW_KEY_D) == GLFW_PRESS) {
        this->camera->MoveRight();
    }

    if (window->GetKey(GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->camera->MoveUp();
    }

    if (window->GetKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        this->camera->MoveDown();
    }
}

void CameraControll::Update(Subject* subject, const char* type, void* data)
{
    if (strcmp(type, "cursor_move") == 0) {
        glm::vec2 mouse_pos = *static_cast<glm::vec2*>(data);

        MouseMovement(mouse_pos.x, mouse_pos.y);
    }
}