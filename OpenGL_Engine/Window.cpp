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

void Window::UpdateViewportSize()
{
	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}