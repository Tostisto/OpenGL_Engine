#pragma once

#include "GLFW/glfw3.h"
#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "Callback.h"

class Window : public Observer, public Subject
{
public:

	GLFWwindow* window;
	int width;
	int height;

	Window(int width, int height);
	~Window();

	void UpdateViewportSize();

	void BindCallbacks();

	glm::mat4 GetProjectionMatrix();

	bool GetKey(int key);

	void Update(Subject* subject, const char* type, void* data);
};

