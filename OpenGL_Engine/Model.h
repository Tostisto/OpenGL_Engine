#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ShaderProgram.h"

class Model
{
	GLuint VBO = 0;
	GLuint VAO = 0;

	float* points;

	public:
		Model(float* points, int numPoints);
		~Model();

		void Draw();
};

