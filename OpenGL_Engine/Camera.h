#pragma once

#include "Window.h"

#include "Observer.h"
#include "Subject.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class Camera : public Subject, public Observer
{
private:
    float last_x = 0;
    float last_y = 0;

    float yaw = -90.0f; // Rotation around y axis
    float pitch = 0.0f; // Rotation around x axis

    glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

public:
    Camera();

    glm::mat4 GetViewMatrix();
    glm::vec3 GetCameraPosition();

    void CameraMovement(Window* window);
    void MouseMovement(float x_pos, float y_pos);

    void Update(Subject* subject);
};

