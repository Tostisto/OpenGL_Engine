#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexShader.h"
#include "FragmentShader.h"

#include "Observer.h"

#include "Camera.h"

class ShaderProgram : public Observer
{
	GLuint programID;

	VertexShader* vertexShader;
	FragmentShader* fragmentShader;

	glm::mat4 viewMatrix;

	const char* ShaderType;

	void AttachShaders();
	void LinkProgram();
	void CheckProgram();

public:
	ShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader, const char* ShaderType);
	
	void UseProgram();
	void setUniform(const char* name, glm::mat4 matrix);
	void setUniform(const char* name, glm::vec3 vector);

	GLuint GetProgramID();
	void SetViewMatrix();


	void Update(Subject* subject, const char* type, void* data);
};

