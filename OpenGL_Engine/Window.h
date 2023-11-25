#pragma once

#include "GLFW/glfw3.h"
#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "Callback.h"

class Window : public Observer, public Subject
{
private:
	float fov = 45.0f;

public:
	GLFWwindow* window;
	int width;
	int height;

	Window(int width, int height, const char* window_title);
	~Window();

	void BindCallbacks();
	bool GetKey(int key);

	void UpdateViewportSize();
	void UpdateFov(glm::vec2 offset);
	glm::mat4 GetProjectionMatrix();

	void Update(Subject* subject, const char* type, void* data);
};