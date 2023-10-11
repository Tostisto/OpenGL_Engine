#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "Subject.h"

class Callback : public Subject
{

private:
	static Callback* instance;

	Callback() = default;

	double mouse_x = 0;
	double mouse_y = 0;

public:
	static Callback* GetInstance();

	void RegisterCallbacks();

	static void ErrorCallback(int error, const char* description);

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void WindowFocusCallback(GLFWwindow* window, int focused);
	void WindowIconifyCallback(GLFWwindow* window, int iconified);
	void WindowSizeCallback(GLFWwindow* window, int width, int height);
	void CursorCallback(GLFWwindow* window, double xpos, double ypos);
	void ButtonCallback(GLFWwindow* window, int button, int action, int mods);

	double GetMouseX();
	double GetMouseY();
};

