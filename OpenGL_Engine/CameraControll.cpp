#include "CameraControll.h"

CameraControll::CameraControll(Camera* camera, Window* window)
{
	this->camera = camera;
	this->window = window;
}

void CameraControll::MouseMovement(float x_pos, float y_pos)
{
    float x_offset = x_pos - last_x;
    float y_offset = last_y - y_pos;
    last_x = x_pos;
    last_y = y_pos;

    glm::vec2 offset = glm::vec2(x_offset, y_offset);

    offset = this->camera->ApplyMouseSensitivity(offset);
    this->camera->UpdateCameraOrientation(offset);
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