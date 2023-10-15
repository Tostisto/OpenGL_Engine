#pragma once

#include "Observer.h"
#include "Camera.h"
#include "Window.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class CameraControll : public Observer
{
private:
	Camera* camera;
	Window* window;

	float last_x = 0;
	float last_y = 0;

public:
	CameraControll(Camera* camera, Window* window);

	void MouseMovement(float x_pos, float y_pos);
	void KeyboardMovement();

	void Update(Subject* subject, const char* type, void* data);
};