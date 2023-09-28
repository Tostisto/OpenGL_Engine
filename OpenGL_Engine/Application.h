#pragma once

//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

#include "Window.h"
#include "Scene.h"

#include "Model.h"

#include "VertexShader.h"
#include "FragmentShader.h"

#include "ShaderProgram.h"


#include "Scene.h"

class Application
{

private:
	Window* window;
	Scene* scene;

public:
	Application();

	void InitGLFW();
	void InitGLEW();

	void OpenGLVersion();
	void InitVersions(int major_version, int minor_version);

	void Run();
};