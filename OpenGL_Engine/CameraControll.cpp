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
            this->last_y = this->window->height - 1;
 			glfwSetCursorPos(this->window->window, this->current_x, this->window->height - 1);
		}
	}
    else if (this->current_y >= this->window->height - 1) {
        if (this->camera->GetPitch() > -90.0f) {
            this->last_y = 0;
            glfwSetCursorPos(this->window->window, this->current_x, 0);
        }
	}
}

CameraControll::CameraControll(Camera* camera, Window* window, ModelsManipulation* modelsManipulation)
{
	this->camera = camera;
	this->window = window;
    this->modelsManipulation = modelsManipulation;

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


glm::vec3 CameraControll::ScreenToWorldCoordinates(int x, int y, GLfloat depth) {
    glm::vec4 viewport = glm::vec4(0.0f, 0.0f, this->window->width, this->window->height);
    return glm::vec3(x, this->window->height - y, depth);
}

glm::vec3 CameraControll::CalculateWorldPosition(glm::vec3 wincoord) {
    glm::vec4 viewport = glm::vec4(0.0f, 0.0f, this->window->width, this->window->height);

    return glm::unProject(wincoord, this->camera->GetViewMatrix(), window->GetProjectionMatrix(), viewport);
}

void CameraControll::GetClickerPixelVariables(GLbyte color[4], GLfloat& depth, GLuint& index)
{
    double new_y = this->window->height - this->current_y;

    glReadPixels(current_x, new_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(current_x, new_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(current_x, new_y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
}

glm::vec3 CameraControll::GetMouseClickPosition(GLfloat depth)
{
    glm::vec3 wincoord = ScreenToWorldCoordinates(current_x, current_y, depth);
    glm::vec3 pos = CalculateWorldPosition(wincoord);

    return pos;
}

void CameraControll::ModelPicker()
{
    GLbyte color[4];
    GLfloat depth;
    GLuint index;

    GetClickerPixelVariables(color, depth, index);

    if (depth == 1.0f) {
		printf("No model picked\n");
		return;
	}

    glm::vec3 mouseClickPosition = GetMouseClickPosition(depth);
    
    //// Remove model
    //this->modelsManipulation->RemoveModel(index);

    this->modelsManipulation->AddModel(mouseClickPosition);
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
    else if (strcmp(type, "c_key_press") == 0) {
        this->camera->CameraSpotLightControll();
	}
    else if (strcmp(type, "right_mouse_button") == 0)
    {
        ModelPicker();
    }
}