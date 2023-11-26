#include "Window.h"

Window::Window(int width, int height, const char* window_title)
{
	this->width = width;
	this->height = height;

	this->window = glfwCreateWindow(this->width, this->height, window_title, NULL, NULL);

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
	if (this->height != 0 || this->width != 0)
	{
		glViewport(0, 0, width, height);

		Notify(WINDOW_RESIZED, new glm::vec2(width, height));
	}
}

void Window::UpdateFov(glm::vec2 offset)
{
	this->fov -= offset.y;

	if (this->fov < 1.0f)
		this->fov = 1.0f;
	else if (this->fov > 100.0f)
		this->fov = 100.0f;

	glm::vec3 perspective_data = glm::vec3(fov, this->width, (float)this->height);

	Notify(FOV_CHANGED, &perspective_data);
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

	// Scroll callback
	glfwSetScrollCallback(window, [](GLFWwindow* w, double xoffset, double yoffset) {Callback::GetInstance()->ScrollCallback(w, xoffset, yoffset); });
}

glm::mat4 Window::GetProjectionMatrix()
{
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), this->width / (float)this->height, 0.1f, 100.0f);
	return projectionMatrix;
}

bool Window::GetKey(int key)
{
	return glfwGetKey(this->window, key);
}

void Window::Update(Subject* subject, Event type, void* data)
{
	if (type == WINDOW_RESIZED) {
		glm::vec2 window_size = *static_cast<glm::vec2*>(data);

		this->width = window_size.x;
		this->height = window_size.y;

		this->UpdateViewportSize();
	}
	else if (type == MOUSE_SCROLL) {

		glm::vec2 scroll_offset = *static_cast<glm::vec2*>(data);

		this->UpdateFov(scroll_offset);
	}
}