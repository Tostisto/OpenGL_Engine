#include "Scene.h"

#include "sphere.h"
#include "suzi_smooth.h"

Scene::Scene(Window* window)
{
	this->window = window;

	this->drawables = std::vector<Drawable*>();

	// Constant Shader
	VertexShader* constantVertexShader = new VertexShader("Shaders\\constant.vert");
	FragmentShader* constantFragmentShader = new FragmentShader("Shaders\\constant.frag");
	ShaderProgram* constantShaderProgram = new ShaderProgram(constantVertexShader, constantFragmentShader);
	this->shaderPrograms.push_back(constantShaderProgram);

	// Lambert Shader 
	VertexShader* lamberVertexShader = new VertexShader("Shaders\\lambert.vert");
	FragmentShader* lamberFragmentShader = new FragmentShader("Shaders\\lambert.frag");
	ShaderProgram* lambertShaderProgram = new ShaderProgram(lamberVertexShader, lamberFragmentShader);

	this->shaderPrograms.push_back(lambertShaderProgram);

	// Phong Shader 
	VertexShader* phongVertexShader = new VertexShader("Shaders\\phong.vert");
	FragmentShader* phongFragmentShader = new FragmentShader("Shaders\\phong.frag");
	ShaderProgram* phongShaderProgram = new ShaderProgram(phongVertexShader, phongFragmentShader);

	this->shaderPrograms.push_back(phongShaderProgram);


	ModelLoader* modelLoader = new ModelLoader("C:\\Users\\kubac\\Desktop\\model.obj");

	// Model 1
	Model* model = new Model(modelLoader->getVertices(), modelLoader->getVerticesSize()/6, 6);
	Drawable* drawable = new Drawable(model);
	drawable->AddTransformation(new Translation(glm::vec3(3.0f, 0.0f, 0.0f)));
	drawable->AddTransformation(new Rotation(static_cast<float>(glm::radians(50.0)), glm::vec3(1.0f, 1.0f, 1.0f)));
	drawable->AddTransformation(new Scale(glm::vec3(0.0004f, 0.0004f, 0.0004f)));
	drawable->LinkShaderProgram(shaderPrograms[2]);

	this->AddDrawable(drawable);

	// Model 2
	Model* model2 = new Model(suziSmooth, 2904, 6);
	Drawable* drawable2 = new Drawable(model2);
	drawable2->AddTransformation(new Translation(glm::vec3(-3.0f, 0.0f, 0.0f)));
	drawable2->LinkShaderProgram(shaderPrograms[2]);

	this->AddDrawable(drawable2);

	// Model 3
	Model* model3 = new Model(sphere, 2880, 6);
	Drawable* drawable3 = new Drawable(model3);
	drawable3->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	drawable3->LinkShaderProgram(shaderPrograms[2]);

	this->AddDrawable(drawable3);

	// Camera
	this->camera = new Camera();

	// Light
	this->light = new Light();


	this->cameraControll = new CameraControll(this->camera, this->window);
	Callback::GetInstance()->Attach(this->cameraControll);

	// Projection matrix
	glm::mat4 projectionMatrix = this->window->GetProjectionMatrix();


	this->camera->Attach(shaderPrograms[2]);
	this->light->Attach(shaderPrograms[2]);

	for (int i = 0; i < this->shaderPrograms.size(); i++) {

		this->shaderPrograms[i]->UseProgram();
		this->shaderPrograms[i]->setUniform("projectionMatrix", projectionMatrix);
	}


	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		this->window->Attach(this->shaderPrograms[i]);
	}

	this->light->setPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	this->light->setColor(glm::vec3(0.2f, 0.2f, 0.2f));
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

void Scene::Render()
{
	this->cameraControll->KeyboardMovement();

	for (int i = 0; i < this->drawables.size(); i++) {
		this->drawables[i]->Render();
	}
}