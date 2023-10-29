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

void Scene::AddLight(Light* light)
{
	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		light->Attach(shaderPrograms[i]);
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