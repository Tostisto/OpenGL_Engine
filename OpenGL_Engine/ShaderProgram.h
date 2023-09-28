#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexShader.h"
#include "FragmentShader.h"

class ShaderProgram
{
	GLuint programID;

	VertexShader *vertexShader;
	FragmentShader *fragmentShader;

	void AttachShaders();
	void LinkProgram();

	void CheckProgram();

	public:
		ShaderProgram(VertexShader *vertexShader, FragmentShader *fragmentShader);

		GLuint GetProgramID();
		void UseProgram();
};

