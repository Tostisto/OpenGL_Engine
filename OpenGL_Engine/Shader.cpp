#include "Shader.h"

Shader::Shader(GLenum shaderType, const char* shaderPath) {
	this->shaderType = shaderType;
	this->shaderPath = shaderPath;

	ShaderLoader shaderLoader = ShaderLoader(shaderPath);
	this->shaderSource = shaderLoader.GetShaderCode();

	this->shaderID = glCreateShader(shaderType);
	this->CompileShader();
}

void Shader::CompileShader()
{
	glShaderSource(shaderID, 1, &this->shaderSource, NULL);
	glCompileShader(shaderID);

	this->CheckShaderCompilation();
}

GLuint Shader::GetShaderID()
{
	return this->shaderID;
}

void Shader::CheckShaderCompilation()
{
	GLint success;
	glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(this->shaderID, 512, nullptr, infoLog);
		printf("Shader compilation failed: %s\n", infoLog);

		exit(EXIT_FAILURE);
	}
}