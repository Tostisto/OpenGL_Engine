#include "Scene.h"

Scene::Scene(Window* window)
{
	this->window = window;

	this->camera = new Camera();

	modelsManipulation = new ModelsManipulation(&this->drawables);

	this->cameraControll = new CameraControll(this->camera, this->window, modelsManipulation);

	AddCameraControll(this->cameraControll);

}

void Scene::AddCameraControll(CameraControll* cameraControll)
{
	this->cameraControll = cameraControll;
	Callback::GetInstance()->Attach(cameraControll);
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

	shaderProgram->UseProgram();

	this->camera->Attach(shaderProgram);
	this->window->Attach(shaderProgram);

	shaderProgram->setUniform("viewMatrix", this->camera->GetViewMatrix());
	shaderProgram->setUniform("projectionMatrix", this->window->GetProjectionMatrix());

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

void Scene::AddModelPickers(Model* model, ShaderProgram* shaderProgram)
{
	this->modelsManipulation->AddDrawableModel(model, shaderProgram);
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

				uniformName = "lights[" + std::to_string(light->getLightIndex()) + "].attenuation";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), ((PointLight*)light)->getAttenuation());

			}
			else if (light->getLightType() == LightType::SPOT_LIGHT) {
				uniformName = "lights[" + std::to_string(light->getLightIndex()) + "]";

				this->shaderPrograms[i]->setUniform(uniformName.c_str(), (SpotLight*)light);

				uniformName = "lights[" + std::to_string(light->getLightIndex()) + "].attenuation";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), ((PointLight*)light)->getAttenuation());
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
