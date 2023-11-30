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
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		Notify(C_KEY_PRESSED, nullptr);
	}

	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
	{
		bool left_ctrl_pressed = true;

		Notify(LEFT_CTRL_PRESSED, &left_ctrl_pressed);
	}
	else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
	{
		bool left_ctrl_pressed = false;

		Notify(LEFT_CTRL_PRESSED, &left_ctrl_pressed);
	}
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

	Notify(WINDOW_RESIZED, &window_size);
}

void Callback::CursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec2 mouse_pos = glm::vec2(xpos, ypos);

	Notify(CURSOR_MOVED, &mouse_pos);
}

void Callback::ButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		bool left_button_pressed = true;

		Notify(LEFT_MOUSE_BUTTON_PRESSED, &left_button_pressed);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		bool left_button_pressed = false;

		Notify(LEFT_MOUSE_BUTTON_PRESSED, &left_button_pressed);
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		Notify(RIGHT_MOUSE_BUTTON_PRESSED, nullptr);
	}
}

void Callback::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	glm::vec2 scroll_offset = glm::vec2(xoffset, yoffset);

	Notify(MOUSE_SCROLL, &scroll_offset);
}