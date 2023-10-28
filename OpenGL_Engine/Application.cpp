#include "Application.h"

Application::Application()
{
	this->InitGLFW();

	//this->InitVersions(3, 3);

	this->window = new Window(1080, 720);
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
	//TestScene* scene = new TestScene();
	//PhongTestScene* scene = new PhongTestScene();
	MultipleModelsScene* scene = new MultipleModelsScene();
	//SolarSystemScene* scene = new SolarSystemScene();

	scene->Create(this->window);

	Callback* callback = Callback::GetInstance();
	callback->RegisterCallbacks();
	callback->Attach(this->window);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(this->window->window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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