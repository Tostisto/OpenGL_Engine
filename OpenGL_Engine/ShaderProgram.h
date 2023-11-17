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

#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

#include "ShaderType.h"


class ShaderProgram : public Observer
{
	GLuint programID;

	VertexShader* vertexShader;
	FragmentShader* fragmentShader;

	glm::mat4 viewMatrix;

	void AttachShaders();
	void LinkProgram();
	void CheckProgram();

public:
	ShaderType shaderType;

	ShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader, ShaderType shaderType);
	~ShaderProgram();
	
	void UseProgram();

	bool checkUniform(GLint location, const char* name);
	void setUniform(const char* name, glm::mat4 matrix);
	void setUniform(const char* name, glm::vec3 vector);
	void setUniform(const char* name, float value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, PointLight* pointLight);
	void setUniform(const char* name, DirectionalLight* directionalLight);
	void setUniform(const char* name, SpotLight* spotLight);
	void setUniform(const char* name, CameraSpotLight* cameraSpotLight);
	void setUniform(const char* name, GLuint textureID);

	void setShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader, ShaderType shaderType);

	void SetViewMatrix();

	void Update(Subject* subject, const char* type, void* data);
};