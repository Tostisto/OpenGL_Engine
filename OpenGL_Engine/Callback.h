#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <stdio.h>
#include <stdlib.h>

#include "Subject.h"

class Callback : public Subject
{
private:
	static Callback* instance;

	double mouse_x = 0;
	double mouse_y = 0;

	Callback() = default;
	static void ErrorCallback(int error, const char* description);

public:
	static Callback* GetInstance();

	void RegisterCallbacks();

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void WindowFocusCallback(GLFWwindow* window, int focused);
	void WindowIconifyCallback(GLFWwindow* window, int iconified);
	void WindowSizeCallback(GLFWwindow* window, int width, int height);
	void CursorCallback(GLFWwindow* window, double xpos, double ypos);
	void ButtonCallback(GLFWwindow* window, int button, int action, int mods);

	double GetMouseX();
	double GetMouseY();
};

