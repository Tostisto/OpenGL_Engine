#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader, const char* ShaderType)
{
	this->programID = glCreateProgram();

	this->vertexShader = vertexShader;
	this->fragmentShader = fragmentShader;

	this->ShaderType = ShaderType;

	this->AttachShaders();
	this->LinkProgram();
	this->CheckProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(this->programID);

	delete this->vertexShader;
	delete this->fragmentShader;
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

void ShaderProgram::SetViewMatrix()
{
	GLint idModelTransform = glGetUniformLocation(this->programID, "viewMatrix");

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

	GLint idModelTransform = glGetUniformLocation(this->programID, name);

	if (idModelTransform == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", name);
		exit(EXIT_FAILURE);
	}

	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::setUniform(const char* name, glm::vec3 vector)
{
	this->UseProgram();

	GLint idModelTransform = glGetUniformLocation(this->programID, name);

	if (idModelTransform == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", name);
		exit(EXIT_FAILURE);
	}

	glUniform3fv(idModelTransform, 1, glm::value_ptr(vector));
}

void ShaderProgram::setUniform(const char* name, float value)
{
	this->UseProgram();

	GLint idModelTransform = glGetUniformLocation(this->programID, name);

	if (idModelTransform == -1)
	{
		fprintf(stderr, "Could not bind uniform %s\n", name);
		exit(EXIT_FAILURE);
	}

	glUniform1f(idModelTransform, value);
}

void ShaderProgram::setShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader)
{
	if (this->vertexShader != nullptr)
	{
		delete this->vertexShader;
	}

	if (this->fragmentShader != nullptr)
	{
		delete this->fragmentShader;
	}

	this->vertexShader = vertexShader;
	this->fragmentShader = fragmentShader;
}

void ShaderProgram::Update(Subject* subject, const char* type, void* data)
{
	if (strcmp(type, "camera") == 0)
	{
		Camera* camera = (Camera*)subject;

		glm::mat4 viewMatrix = camera->GetViewMatrix();

		this->viewMatrix = viewMatrix;

		glm::vec3 cameraPos = camera->GetCameraPos();


		if (this->ShaderType != "constantShaderProgram" && this->ShaderType != "lambertShaderProgram")
		{
			this->setUniform("cameraPos", cameraPos);
		}
		
		this->setUniform("viewMatrix", viewMatrix);
	}
	else if (strcmp(type, "window_resize") == 0)
	{
		glm::vec2* size = (glm::vec2*)data;

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), size->x / (float)size->y, 0.1f, 100.0f);

		this->setUniform("projectionMatrix", projectionMatrix);
	}
	else if (strcmp(type, "fov_change") == 0)
	{
		printf("fov_change \n");

		glm::vec3 *new_data = (glm::vec3*)data;

		float fov = new_data->x;
		float width = new_data->y;
		float height = new_data->z;

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), width / (float)height, 0.1f, 100.0f);

		this->setUniform("projectionMatrix", projectionMatrix);
	}
	else if (strcmp(type, "light_position") == 0)
	{
		printf("light position\n");

		if (this->ShaderType != "constantShaderProgram")
		{
			this->setUniform("lightPos", *(glm::vec3*)data);
		}
	}
	else if (strcmp(type, "light_color") == 0)
	{
		printf("light color\n");

		if (this->ShaderType != "constantShaderProgram")
		{
			this->setUniform("lightColor", *(glm::vec3*)data);
		}
	}
}