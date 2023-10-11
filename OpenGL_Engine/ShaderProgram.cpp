#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader)
{
	this->programID = glCreateProgram();

	this->vertexShader = vertexShader;
	this->fragmentShader = fragmentShader;

	this->AttachShaders();
	this->LinkProgram();
	this->CheckProgram();
}

void ShaderProgram::AttachShaders()
{
	glAttachShader(this->programID, this->fragmentShader->GetShaderID());
	glAttachShader(this->programID, this->vertexShader->GetShaderID());
}

void ShaderProgram::LinkProgram()
{
	glLinkProgram(this->programID);
}

void ShaderProgram::CheckProgram()
{
	GLint status;
	glGetProgramiv(this->programID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->programID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;

		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Shader program linked successfully\n");	
	}
}

GLuint ShaderProgram::GetProgramID()
{
	return this->programID;
}

void ShaderProgram::UseProgram()
{
	glUseProgram(this->programID);
}

void ShaderProgram::setUniform(const char* name, glm::mat4 matrix)
{
	GLint idModelTransform = glGetUniformLocation(this->GetProgramID(), name);

	if (idModelTransform == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", name);
		exit(EXIT_FAILURE);
	}

	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::Update(Subject* subject)
{
	// TOOD: Update shader program

	//fprintf(stdout, "ShaderProgram::Update()\n");

	Camera* camera = (Camera*)subject;

	glm::mat4 viewMatrix = camera->GetViewMatrix();

	// now i need to send to shader using uniform
	this->setUniform("viewMatrix", viewMatrix);

	fprintf(stdout, "ShaderProgram::Update() - viewMatrix\n");
}
