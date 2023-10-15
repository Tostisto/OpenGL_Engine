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

void ShaderProgram::SetViewMatrix()
{
	GLint idModelTransform = glGetUniformLocation(this->GetProgramID(), "viewMatrix");

	if (idModelTransform == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", "viewMatrix");
		exit(EXIT_FAILURE);
	}

	this->setUniform("viewMatrix", this->viewMatrix);
}


void ShaderProgram::UseProgram()
{
	glUseProgram(this->programID);
}

void ShaderProgram::setUniform(const char* name, glm::mat4 matrix)
{
	this->UseProgram();

	GLint idModelTransform = glGetUniformLocation(this->GetProgramID(), name);

	if (idModelTransform == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", name);
		exit(EXIT_FAILURE);
	}

	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::Update(Subject* subject, const char* type, void* data)
{
	if (strcmp(type, "camera") == 0)
	{
		Camera* camera = (Camera*)subject;

		glm::mat4 viewMatrix = camera->GetViewMatrix();

		this->viewMatrix = viewMatrix;

		this->setUniform("viewMatrix", viewMatrix);
	}
	else if (strcmp(type, "window_resize") == 0)
	{
		glm::vec2* size = (glm::vec2*)data;

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), size->x / (float)size->y, 0.1f, 100.0f);

		this->setUniform("projectionMatrix", projectionMatrix);
	}
}