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

void Scene::AddDrawable(Drawable* drawable)
{
	this->drawables.push_back(drawable);
}

void Scene::RemoveDrawable(Drawable* drawable)
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

void Scene::UpdateFrame()
{
}

void Scene::Render()
{
	this->cameraControll->KeyboardMovement();

	UpdateFrame();

 	for (int i = 0; i < this->drawables.size(); i++) {
		this->drawables[i]->Render();
	}
}

void Scene::AddLight(Light* light)
{
	this->lights.push_back(light);

	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		light->Attach(shaderPrograms[i]);
	}


	std::string uniformName;

	// send light data to shaders
	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		this->shaderPrograms[i]->UseProgram();

		if (this->shaderPrograms[i]->ShaderType == "phongShaderProgram" || this->shaderPrograms[i]->ShaderType == "blinnShaderProgram" || this->shaderPrograms[i]->ShaderType == "lambertShaderProgram")
		{
			if (light->getLightType() == LightType::DIRECTIONAL_LIGHT) {

				uniformName = "lights[" + std::to_string(lights.size() - 1) + "].direction";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), ((DirectionalLight*)light)->getDirection());

				uniformName = "lights[" + std::to_string(lights.size() - 1) + "].color";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), light->getColor());

				uniformName = "lights[" + std::to_string(lights.size() - 1) + "].type";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), light->getLightType());
			}
			else if (light->getLightType() == LightType::POINT_LIGHT) {

				uniformName = "lights[" + std::to_string(lights.size() - 1) + "].position";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), ((PointLight*)light)->getPosition());

				uniformName = "lights[" + std::to_string(lights.size() - 1) + "].color";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), light->getColor());

				uniformName = "lights[" + std::to_string(lights.size() - 1) + "].type";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), light->getLightType());
			}
			else if (light->getLightType() == LightType::SPOT_LIGHT) {

				uniformName = "lights[" + std::to_string(lights.size() - 1) + "].position";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), ((SpotLight*)light)->getPosition());

				uniformName = "lights[" + std::to_string(lights.size() - 1) + "].color";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), light->getColor());

				uniformName = "lights[" + std::to_string(lights.size() - 1) + "].type";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), light->getLightType());

				uniformName = "lights[" + std::to_string(lights.size() - 1) + "].direction";
				this->shaderPrograms[i]->setUniform(uniformName.c_str(), ((SpotLight*)light)->getDirection());
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
