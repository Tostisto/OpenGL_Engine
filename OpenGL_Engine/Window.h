#pragma once

#include "GLFW/glfw3.h"
#include <stdio.h>
#include <stdlib.h>

class Window
{

public:

	GLFWwindow* window;
	int width;
	int height;

	Window(int width, int height);
	~Window();

	void UpdateViewportSize();
};

