#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ShaderProgram.h"

class Model
{
private:
	GLuint VBO = 0;
	GLuint VAO = 0;

	float* points;
	int numPoints;

public:
	Model(float* points, int numPoints, int pointSize);
	~Model();

	void Draw();
};

