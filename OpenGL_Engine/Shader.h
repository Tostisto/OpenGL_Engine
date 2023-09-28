#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>

#include "ShaderLoader.h"

class Shader
{
public:
	Shader(GLenum shaderType, const char* shaderPath);
	void CompileShader();
	GLuint GetShaderID();

protected:
	GLuint shaderID;
	GLenum shaderType;
	const char* shaderPath;
	const char* shaderSource;

	void CheckShaderCompilation();
};