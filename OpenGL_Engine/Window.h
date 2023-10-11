#pragma once

#include "GLFW/glfw3.h"
#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "Callback.h"

#include "Observer.h"
#include "Subject.h"

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

	void Update(Subject* subject);



	// Test
	// Get Key
	bool GetKey(int key);
};

