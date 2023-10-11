#include "Callback.h"

Callback* Callback::instance = nullptr;

Callback* Callback::GetInstance()
{
	if (instance == nullptr)
		instance = new Callback();

	return instance;
}

void Callback::RegisterCallbacks()
{
	glfwSetErrorCallback(ErrorCallback);
}


void Callback::ErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void Callback::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Callback::WindowFocusCallback(GLFWwindow* window, int focused)
{
	fprintf(stdout, "Window focus callback\n");
}

void Callback::WindowIconifyCallback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Callback::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Callback::CursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	printf("cursor_callback \n");
	mouse_x = xpos;
	mouse_y = ypos;
	Notify();
}

void Callback::ButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	printf("button_callback \n");
}

double Callback::GetMouseX()
{
	return mouse_x;
}

double Callback::GetMouseY()
{
	return mouse_y;
}
