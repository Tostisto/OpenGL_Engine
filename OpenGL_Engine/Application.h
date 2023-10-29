#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include <stdlib.h>
#include <stdio.h>

#include "TestScene.h"
#include "PhongTestScene.h"
#include "MultipleModelsScene.h"
#include "SolarSystemScene.h"

#include "Callback.h"

class Application
{

private:
	Window* window;

public:
	Application();

	void InitGLFW();
	void InitGLEW();

	void OpenGLVersion();
	void InitVersions(int major_version, int minor_version);

	void Run();
};