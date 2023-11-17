#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader, ShaderType shaderType)
{
	this->programID = glCreateProgram();

	this->vertexShader = vertexShader;
	this->fragmentShader = fragmentShader;

	this->shaderType = shaderType;

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

bool ShaderProgram::checkUniform(GLint location, const char* name)
{
	if (location == -1) {
		fprintf(stderr, "Could not bind uniform %s in %d with id:%d", name, this->shaderType, this->programID);
		return false;
	}
	return true;
}

void ShaderProgram::setUniform(const char* name, glm::mat4 matrix)
{
	this->UseProgram();

	GLint idModelTransform = glGetUniformLocation(this->programID, name);

	if (!checkUniform(idModelTransform, name)) {
		exit(EXIT_FAILURE);
	}

	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::setUniform(const char* name, glm::vec3 vector)
{
	this->UseProgram();

	GLint idModelTransform = glGetUniformLocation(this->programID, name);

	if (!checkUniform(idModelTransform, name)) {
		exit(EXIT_FAILURE);
	}

	glUniform3fv(idModelTransform, 1, glm::value_ptr(vector));
}

void ShaderProgram::setUniform(const char* name, float value)
{
	this->UseProgram();

	GLint idModelTransform = glGetUniformLocation(this->programID, name);

	if (!checkUniform(idModelTransform, name)) {
		exit(EXIT_FAILURE);
	}

	glUniform1f(idModelTransform, value);
}

void ShaderProgram::setUniform(const char* name, int value)
{
	this->UseProgram();

	GLint idModelTransform = glGetUniformLocation(this->programID, name);

	if (!checkUniform(idModelTransform, name)) {
		exit(EXIT_FAILURE);
	}

	glUniform1i(idModelTransform, value);
}

void ShaderProgram::setUniform(const char* name, PointLight* pointLight)
{
	std::string uniformName;

	uniformName = name + std::string(".position");
	this->setUniform(uniformName.c_str(), pointLight->getPosition());

	uniformName = name + std::string(".color");
	this->setUniform(uniformName.c_str(), pointLight->getColor());

	uniformName = name + std::string(".type");
	this->setUniform(uniformName.c_str(), pointLight->getLightType());
}

void ShaderProgram::setUniform(const char* name, DirectionalLight* directionalLight)
{
	std::string uniformName;

	uniformName = name + std::string(".direction");
	this->setUniform(uniformName.c_str(), directionalLight->getDirection());

	uniformName = name + std::string(".color");
	this->setUniform(uniformName.c_str(), directionalLight->getColor());

	uniformName = name + std::string(".type");
	this->setUniform(uniformName.c_str(), directionalLight->getLightType());
}

void ShaderProgram::setUniform(const char* name, SpotLight* spotLight)
{
	std::string uniformName;

	uniformName = name + std::string(".position");
	this->setUniform(uniformName.c_str(), spotLight->getPosition());

	uniformName = name + std::string(".color");
	this->setUniform(uniformName.c_str(), spotLight->getColor());

	uniformName = name + std::string(".type");
	this->setUniform(uniformName.c_str(), spotLight->getLightType());

	uniformName = name + std::string(".direction");
	this->setUniform(uniformName.c_str(), spotLight->getDirection());

	uniformName = name + std::string(".cutOff");
	this->setUniform(uniformName.c_str(), spotLight->getCutOff());
}

void ShaderProgram::setUniform(const char* name, CameraSpotLight* cameraSpotLight)
{
	std::string uniformName;

	uniformName = name + std::string(".position");
	this->setUniform(uniformName.c_str(), cameraSpotLight->getPosition());

	uniformName = name + std::string(".color");
	this->setUniform(uniformName.c_str(), cameraSpotLight->getColor());

	uniformName = name + std::string(".direction");
	this->setUniform(uniformName.c_str(), cameraSpotLight->getDirection());

	uniformName = name + std::string(".cutOff");
	this->setUniform(uniformName.c_str(), cameraSpotLight->getCutOff());

	uniformName = name + std::string(".enabled");
	this->setUniform(uniformName.c_str(), cameraSpotLight->isEnabled());
}

void ShaderProgram::setUniform(const char* name, GLuint textureID)
{
	this->UseProgram();

	GLint idModelTransform = glGetUniformLocation(this->programID, name);

	if (!checkUniform(idModelTransform, name)) {
		exit(EXIT_FAILURE);
	}

	glUniform1i(idModelTransform, textureID);
}

void ShaderProgram::setShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader, ShaderType shaderType)
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
	this->shaderType = shaderType;

	this->AttachShaders();
	this->LinkProgram();
	this->CheckProgram();
}

void ShaderProgram::Update(Subject* subject, const char* type, void* data)
{
	if (strcmp(type, "camera") == 0)
	{
		Camera* camera = (Camera*)subject;

		glm::mat4 viewMatrix = camera->GetViewMatrix();

		this->viewMatrix = viewMatrix;

		glm::vec3 cameraPos = camera->GetCameraPos();


		if (this->shaderType != ShaderType::CONSTANT &&
			this->shaderType != ShaderType::TEXTURE &&
			this->shaderType != ShaderType::CUBEMAP &&
			this->shaderType != ShaderType::LAMBERT)
		{
			this->setUniform("cameraPos", cameraPos);
		}

		if (this->shaderType != ShaderType::CONSTANT &&
			this->shaderType != ShaderType::TEXTURE &&
			this->shaderType != ShaderType::CUBEMAP)
		{
			// Set camera spot light
			this->setUniform("camera_spot_light", camera->GetCameraSpotLight());
		}

		if (this->shaderType == ShaderType::CUBEMAP)
		{
			// Remove translation from the view matrix
			glm::mat4 view = glm::mat4(glm::mat3(viewMatrix));

			this->setUniform("viewMatrix", view);
		}
		else
		{
			this->setUniform("viewMatrix", viewMatrix);
		}
	}
	else if (strcmp(type, "window_resize") == 0)
	{
		glm::vec2* size = (glm::vec2*)data;

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), size->x / (float)size->y, 0.1f, 100.0f);

		this->setUniform("projectionMatrix", projectionMatrix);
	}
	else if (strcmp(type, "fov_change") == 0)
	{
		glm::vec3 *new_data = (glm::vec3*)data;

		float fov = new_data->x;
		float width = new_data->y;
		float height = new_data->z;

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), width / (float)height, 0.1f, 100.0f);

		this->setUniform("projectionMatrix", projectionMatrix);
	}
	else if (strcmp(type, "light") == 0)
	{
		if (this->shaderType == ShaderType::PHONG ||
			this->shaderType == ShaderType::BLINN_PHONG || 
			this->shaderType == ShaderType::LAMBERT || 
			this->shaderType == ShaderType::TEXTURED_PHONG)
		{
			Light* light = (Light*)subject;

			if (light->getLightType() == LightType::POINT_LIGHT)
			{
				PointLight* pointLight = (PointLight*)light;

				std::string unatchedUniformName = "lights[" + std::to_string(light->getLightIndex()) + "]";

				this->setUniform(unatchedUniformName.c_str(), pointLight);
			}
			else if (light->getLightType() == LightType::DIRECTIONAL_LIGHT)
			{
				DirectionalLight* directionalLight = (DirectionalLight*)light;

				std::string unatchedUniformName = "lights[" + std::to_string(light->getLightIndex()) + "]";

				this->setUniform(unatchedUniformName.c_str(), directionalLight);
			}
			else if (light->getLightType() == LightType::SPOT_LIGHT)
			{
				SpotLight* spotLight = (SpotLight*)light;

				std::string unatchedUniformName = "lights[" + std::to_string(light->getLightIndex()) + "]";

				this->setUniform(unatchedUniformName.c_str(), spotLight);
			}
		}
	}
}