#include "CameraControll.h"

CameraControll::CameraControll(Camera* camera, Window* window)
{
	this->camera = camera;
	this->window = window;

    glfwSetCursorPos(this->window->window, this->window->width / 2, this->window->height / 2);
}

void CameraControll::MouseMovement(float x_pos, float y_pos)
{
    if (lock_camera) {
        float yawChange = last_x - x_pos;
        float pitchChange = last_y - y_pos;

        last_x = x_pos;
        last_y = y_pos;

        glm::vec2 angles = glm::vec2(yawChange, pitchChange);

        angles = this->camera->ApplyMouseSensitivity(angles);

        this->camera->UpdateCameraOrientation(angles);
    }
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

        this->current_x = mouse_pos.x;
        this->current_y = mouse_pos.y;

        MouseMovement(mouse_pos.x, mouse_pos.y);
    }
    else if (strcmp(type, "mouse_button") == 0) {
	    
        bool left_button_pressed = *static_cast<bool*>(data);

        lock_camera = left_button_pressed;

        this->last_x = this->current_x;
        this->last_y = this->current_y;
    }
}