#include "Application.h"

Application::Application()
{
	this->InitGLFW();

	this->window = new Window(2000, 1200, "OpenGL Engine");
	this->window->BindCallbacks();

	this->InitGLEW();

	this->OpenGLVersion();

	this->window->UpdateViewportSize();
}

void Application::InitGLFW()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
}

void Application::InitGLEW()
{
	glewExperimental = GL_TRUE;
	glewInit();
}

void Application::OpenGLVersion()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Application::InitVersions(int major_version, int minor_version)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::Run()
{
	GLint maxTextureUnits;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextureUnits);

	//this->scene = new TestScene(this->window);
	//this->scene = new PhongTestScene(this->window);
	//this->scene = new SolarSystemScene(this->window);
	this->scene = new MultipleModelsScene(this->window);
	//this->scene = new BezierMoveScene(this->window);

	scene->Create();

	Callback* callback = Callback::GetInstance();
	callback->RegisterCallbacks();
	callback->Attach(this->window);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	while (!glfwWindowShouldClose(this->window->window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		scene->Render();

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->window->window);
	}

	glfwDestroyWindow(this->window->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}