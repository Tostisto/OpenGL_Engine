#include "CameraControll.h"

void CameraControll::MouseBorderSwitch()
{
    if (this->current_x <= 0) {
        glfwSetCursorPos(this->window->window, this->window->width - 1, this->current_y);
        this->last_x = this->window->width - 1;
    }
    else if (this->current_x >= this->window->width - 1) {
        glfwSetCursorPos(this->window->window, 0, this->current_y);
        this->last_x = 0;
    }

    if (this->current_y <= 0) {

        if (this->camera->GetPitch() < 90.0f) {
            this->current_x = this->window->height - 1;
            this->last_y = this->window->height - 1;
 			glfwSetCursorPos(this->window->window, this->current_x, this->window->height - 1);
		}
	}
    else if (this->current_y >= this->window->height - 1) {
        if (this->camera->GetPitch() > -90.0f) {
            this->current_x = 0;
            this->last_y = 0;
            glfwSetCursorPos(this->window->window, this->current_x, 0);
        }
	}
}

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

void CameraControll::ModelPicker()
{
    double mouse_x, mouse_y;
    glfwGetCursorPos(window->window, &mouse_x, &mouse_y);

    int window_width, window_height;
    glfwGetFramebufferSize(window->window, &window_width, &window_height);

    GLbyte color[4];
    GLfloat depth;
    GLuint index;

    glReadPixels(mouse_x, mouse_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(mouse_x, mouse_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(mouse_x, mouse_y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    printf("Depth: %f \n", depth);
    printf("Index: %d \n", index);
    printf("Color: %d %d %d %d \n", color[0], color[1], color[2], color[3]);

    glm::vec4 viewport = glm::vec4(0.0f, 0.0f, window_width, window_height);
    glm::vec3 wincoord = glm::vec3(mouse_x, window_height - mouse_y, depth);
    glm::vec3 pos = glm::unProject(wincoord, this->camera->GetViewMatrix(), window->GetProjectionMatrix(), viewport);

    printf("Model: %d\n", index);
    printf("Pos: %f %f %f\n", pos.x, pos.y, pos.z);

}

void CameraControll::Update(Subject* subject, const char* type, void* data)
{
    if (strcmp(type, "cursor_move") == 0) {
        glm::vec2 mouse_pos = *static_cast<glm::vec2*>(data);

        this->current_x = mouse_pos.x;
        this->current_y = mouse_pos.y;

        MouseMovement(mouse_pos.x, mouse_pos.y);

        MouseBorderSwitch();
    }
    else if (strcmp(type, "mouse_button") == 0) {
	    
        bool left_button_pressed = *static_cast<bool*>(data);

        lock_camera = left_button_pressed;

        this->last_x = this->current_x;
        this->last_y = this->current_y;
    }
    else if (strcmp(type, "key_press") == 0) {
        this->camera->CameraSpotLightControll();
	}
    else if (strcmp(type, "right_mouse_button") == 0)
    {
        ModelPicker();
    }
}