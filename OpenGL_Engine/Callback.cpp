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
	

	if (key == GLFW_KEY_C && action == GLFW_PRESS)
		Notify("key_press", nullptr);
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
	glm::vec2 window_size = glm::vec2(width, height);

	Notify("window_resize", &window_size);
}

void Callback::CursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec2 mouse_pos = glm::vec2(xpos, ypos);

	Notify("cursor_move", &mouse_pos);
}

void Callback::ButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		bool left_button_pressed = true;

		Notify("mouse_button", &left_button_pressed);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		bool left_button_pressed = false;

		Notify("mouse_button", &left_button_pressed);
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		Notify("right_mouse_button", nullptr);
	}
}

void Callback::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	glm::vec2 scroll_offset = glm::vec2(xoffset, yoffset);

	Notify("scroll", &scroll_offset);
}