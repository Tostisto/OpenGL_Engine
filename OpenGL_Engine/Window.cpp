#include "Window.h"

Window::Window(int width, int height)
{
	this->width = width;
	this->height = height;

	this->window = glfwCreateWindow(this->width, this->height, "OpenGL Engine", NULL, NULL);

	if (!this->window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);

	glfwSwapInterval(1);
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
}

void Window::UpdateViewportSize()
{
	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Window::BindCallbacks()
{
	// Key callback
	glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods) {Callback::GetInstance()->KeyCallback(w, key, scancode, action, mods); });

	// Window focus callback
	glfwSetWindowFocusCallback(window, [](GLFWwindow* w, int focused) {Callback::GetInstance()->WindowFocusCallback(w, focused); });

	// Window iconify callback
	glfwSetWindowIconifyCallback(window, [](GLFWwindow* w, int iconified) {Callback::GetInstance()->WindowIconifyCallback(w, iconified); });

	// Window size callback
	glfwSetWindowSizeCallback(window, [](GLFWwindow* w, int width, int height) {Callback::GetInstance()->WindowSizeCallback(w, width, height); });

	// Cursor callback
	glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y) {Callback::GetInstance()->CursorCallback(w, x, y);});

	// Button callback
	glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods) {Callback::GetInstance()->ButtonCallback(w, button, action, mods); });
}

glm::mat4 Window::GetProjectionMatrix()
{
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), this->width / (float)this->height, 0.1f, 100.0f);
	return projectionMatrix;
}

bool Window::GetKey(int key)
{
	return glfwGetKey(this->window, key);
}