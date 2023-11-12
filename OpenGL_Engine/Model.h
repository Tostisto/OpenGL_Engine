#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ShaderProgram.h"

#include "ModelType.h"

class Model
{
private:
	GLuint VBO = 0;
	GLuint VAO = 0;

	float* points;
	int numPoints;

	void NoTextureModel();
	void TextureModel();
	void SkyboxModel();

public:
	Model(float* points, int numPoints, ModelType modelType);
	~Model();

	void Draw();
};