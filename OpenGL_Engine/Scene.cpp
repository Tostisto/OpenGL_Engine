#include "Scene.h"

void Scene::AddCameraControll(CameraControll* cameraControll)
{
	this->cameraControll = cameraControll;
	Callback::GetInstance()->Attach(cameraControll);
}

void Scene::AddCamera(Camera* camera)
{
	glm::mat4 viewMatrix = camera->GetViewMatrix();

	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		camera->Attach(shaderPrograms[i]);
		this->shaderPrograms[i]->UseProgram();
		this->shaderPrograms[i]->setUniform("viewMatrix", viewMatrix);
	}
}

void Scene::AddWindow(Window* window)
{
	glm::mat4 projectionMatrix = window->GetProjectionMatrix();

	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		window->Attach(shaderPrograms[i]);
		this->shaderPrograms[i]->UseProgram();
		this->shaderPrograms[i]->setUniform("projectionMatrix", projectionMatrix);
	}
}

void Scene::AddDrawable(DrawableModel* drawable)
{
	this->drawables.push_back(drawable);
}

void Scene::RemoveDrawable(DrawableModel* drawable)
{
	for (int i = 0; i < this->drawables.size(); i++) {
		if (this->drawables[i] == drawable) {
			this->drawables.erase(this->drawables.begin() + i);
			return;
		}
	}
}

void Scene::AddShaderProgram(ShaderProgram* shaderProgram)
{
	this->shaderPrograms.push_back(shaderProgram);
}

void Scene::RemoveShaderProgram(ShaderProgram* shaderProgram)
{
	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		if (this->shaderPrograms[i] == shaderProgram) {
			this->shaderPrograms.erase(this->shaderPrograms.begin() + i);
			return;
		}
	}
}

void Scene::AddCubeMap()
{
	VertexShader* vertex_shader = new VertexShader("Shaders\\cubemap.vert");
	FragmentShader* fragment_shader = new FragmentShader("Shaders\\cubemap.frag");

	ShaderProgram* shader_program = new ShaderProgram(vertex_shader, fragment_shader, ShaderType::CUBEMAP);

	std::vector<const char*> faces = {
		"Textures\\Skybox\\posx.jpg",
		"Textures\\Skybox\\negx.jpg",
		"Textures\\Skybox\\posy.jpg",
		"Textures\\Skybox\\negy.jpg",
		"Textures\\Skybox\\posz.jpg",
		"Textures\\Skybox\\negz.jpg"
	};

	this->cubeMap = new CubeMap(faces);

	this->cubeMap->LinkShaderProgram(shader_program);

	this->AddShaderProgram(shader_program);
}

void Scene::AddCubeMap(std::vector<const char*> faces)
{
	VertexShader* vertex_shader = new VertexShader("Shaders\\cubemap.vert");
	FragmentShader* fragment_shader = new FragmentShader("Shaders\\cubemap.frag");

	ShaderProgram* shader_program = new ShaderProgram(vertex_shader, fragment_shader, ShaderType::CUBEMAP);

	this->cubeMap = new CubeMap(faces);

	this->cubeMap->LinkShaderProgram(shader_program);

	this->AddShaderProgram(shader_program);
}

int Scene::ModelsCount()
{
	return this->drawables.size() + 1;
}

void Scene::UpdateFrame()
{
}

void Scene::Render()
{
	this->cameraControll->KeyboardMovement();

	UpdateFrame();

 	if (this->cubeMap != nullptr) {

		glStencilFunc(GL_ALWAYS, 0, 0xFF);

		this->cubeMap->Render();

		glClear(GL_DEPTH_BUFFER_BIT);
	}

 	for (int i = 0; i < this->drawables.size(); i++) {

		glStencilFunc(GL_ALWAYS, this->drawables[i]->GetModelId(), 0xFF);

		this->drawables[i]->Render();
	}
}

void Scene::AddLight(Light* light)
{
	light->setLightIndex(this->lights.size());

	this->lights.push_back(light);

	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		light->Attach(shaderPrograms[i]);
	}

	std::string uniformName;

	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		this->shaderPrograms[i]->UseProgram();

		if (this->shaderPrograms[i]->shaderType != ShaderType::CONSTANT &&
			this->shaderPrograms[i]->shaderType != ShaderType::TEXTURE &&
			this->shaderPrograms[i]->shaderType != ShaderType::CUBEMAP)
		{
			if (light->getLightType() == LightType::DIRECTIONAL_LIGHT) {
				uniformName = "lights[" + std::to_string(light->getLightIndex()) + "]";

				this->shaderPrograms[i]->setUniform(uniformName.c_str(), (DirectionalLight*)light);
			}
			else if (light->getLightType() == LightType::POINT_LIGHT) {
				uniformName = "lights[" + std::to_string(light->getLightIndex()) + "]";

				this->shaderPrograms[i]->setUniform(uniformName.c_str(), (PointLight*)light);
			}
			else if (light->getLightType() == LightType::SPOT_LIGHT) {
				uniformName = "lights[" + std::to_string(light->getLightIndex()) + "]";

				this->shaderPrograms[i]->setUniform(uniformName.c_str(), (SpotLight*)light);
			}
		}
	}
}

void Scene::RemoveLight(Light* light)
{
	for (int i = 0; i < this->lights.size(); i++) {
		if (this->lights[i] == light) {
			this->lights.erase(this->lights.begin() + i);
			return;
		}
	}
}
