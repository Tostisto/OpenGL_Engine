#include "Scene.h"

#include "sphere.h"
#include "suzi_smooth.h"
#include "tree.h"
#include "gift.h"
#include "plain.h"
#include "bushes.h"

Scene::Scene(Window* window)
{
	this->window = window;

	this->drawables = std::vector<Drawable*>();

	// Constant Shader
	VertexShader* constantVertexShader = new VertexShader("Shaders\\constant.vert");
	FragmentShader* constantFragmentShader = new FragmentShader("Shaders\\constant.frag");
	ShaderProgram* constantShaderProgram = new ShaderProgram(constantVertexShader, constantFragmentShader, "constantShaderProgram");
	this->shaderPrograms.push_back(constantShaderProgram);

	// Lambert Shader 
	VertexShader* lamberVertexShader = new VertexShader("Shaders\\lambert.vert");
	FragmentShader* lamberFragmentShader = new FragmentShader("Shaders\\lambert.frag");
	ShaderProgram* lambertShaderProgram = new ShaderProgram(lamberVertexShader, lamberFragmentShader, "lambertShaderProgram");

	this->shaderPrograms.push_back(lambertShaderProgram);

	// Phong Shader 
	VertexShader* phongVertexShader = new VertexShader("Shaders\\phong.vert");
	FragmentShader* phongFragmentShader = new FragmentShader("Shaders\\phong.frag");
	ShaderProgram* phongShaderProgram = new ShaderProgram(phongVertexShader, phongFragmentShader, "phongShaderProgram");

	this->shaderPrograms.push_back(phongShaderProgram);

	// Blinn shader 
	VertexShader* blinnVertexShader = new VertexShader("Shaders\\blinn.vert");
	FragmentShader* blinnFragmentShader = new FragmentShader("Shaders\\blinn.frag");
	ShaderProgram* blinnShaderProgram = new ShaderProgram(blinnVertexShader, blinnFragmentShader, "blinnShaderProgram");

	this->shaderPrograms.push_back(blinnShaderProgram);

	// Use scene
	Scene3();
	
	// Camera
	this->camera = new Camera();

	// Light
	this->light = new Light();

	this->cameraControll = new CameraControll(this->camera, this->window);
	Callback::GetInstance()->Attach(this->cameraControll);

	// Projection matrix
	glm::mat4 projectionMatrix = this->window->GetProjectionMatrix();

	// Attach
	for (int i = 0; i < this->shaderPrograms.size(); i++) {

		this->light->Attach(shaderPrograms[i]);
		this->camera->Attach(shaderPrograms[i]);

		this->shaderPrograms[i]->UseProgram();
		this->shaderPrograms[i]->setUniform("projectionMatrix", projectionMatrix);
	}

	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		this->window->Attach(this->shaderPrograms[i]);
	}

	this->light->setPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	this->light->setColor(glm::vec3(1.0f, 0.2f, 0.2f));
}

void Scene::Scene1()
{
	Model* model = new Model(sphere, 2880, 6);
	Drawable* drawable = new Drawable(model);
	drawable->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 2.0)));
	drawable->LinkShaderProgram(shaderPrograms[2]);

	this->AddDrawable(drawable);
}

void Scene::Scene2()
{
	Model* model = new Model(sphere, 2880, 6);
	
	Drawable* drawable1 = new Drawable(model);
	drawable1->AddTransformation(new Translation(glm::vec3(2.0, -2.0, 0.0)));
	drawable1->LinkShaderProgram(shaderPrograms[2]);

	this->AddDrawable(drawable1);


	Drawable* drawable2 = new Drawable(model);
	drawable2->AddTransformation(new Translation(glm::vec3(2.0, 2.0, 0.0)));
	drawable2->LinkShaderProgram(shaderPrograms[2]);

	this->AddDrawable(drawable2);


	Drawable* drawable3 = new Drawable(model);
	drawable3->AddTransformation(new Translation(glm::vec3(-2.0, 2.0, 0.0)));
	drawable3->LinkShaderProgram(shaderPrograms[2]);

	this->AddDrawable(drawable3);

	Drawable* drawable4 = new Drawable(model);
	drawable4->AddTransformation(new Translation(glm::vec3(-2.0, -2.0, 0.0)));
	drawable4->LinkShaderProgram(shaderPrograms[2]);

	this->AddDrawable(drawable4);
}

void Scene::Scene3()
{
	// Plain model
	Model* plainModel = new Model(plain, 6, 6);
	Drawable* plainDrawable = new Drawable(plainModel);
	plainDrawable->AddTransformation(new Translation(glm::vec3(0.0f, -1.0f, 0.0f)));
	plainDrawable->AddTransformation(new Scale(glm::vec3(10.0f, 1.0f, 10.0f)));
	plainDrawable->LinkShaderProgram(shaderPrograms[0]);

	this->AddDrawable(plainDrawable);

	// Model 1
	ModelLoader* modelLoader = new ModelLoader("Models\\jeep.obj");

	Model* model = new Model(modelLoader->getVertices(), modelLoader->getVerticesSize()/6, 6);
	Drawable* drawable = new Drawable(model);
	drawable->AddTransformation(new Translation(glm::vec3(2.5f, -0.72f, 3.5f)));
	drawable->AddTransformation(new Scale(glm::vec3(0.0004f, 0.0004f, 0.0004f)));
	drawable->LinkShaderProgram(shaderPrograms[2]);

	this->AddDrawable(drawable);

	// Tree model
	Model* treeModel = new Model(tree, 92814, 6);

	for (int i = 0; i < 10; i++)
	{
		Drawable* treeDrawable = new Drawable(treeModel);
		treeDrawable->AddTransformation(new Translation(glm::vec3(rand() % 10 - 5, -1.0f, rand() % 10 - 5)));
		treeDrawable->AddTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5)));
		treeDrawable->LinkShaderProgram(shaderPrograms[3]);

		this->AddDrawable(treeDrawable);
	}


	// Bushes model
	Model* bushesModel = new Model(bushes, 8730, 6);

	// 100 bushers on plain with random position
	for (int i = 0; i < 100; i++)
	{
		Drawable* bushesDrawable = new Drawable(bushesModel);
		bushesDrawable->AddTransformation(new Translation(glm::vec3(rand() % 10 - 5, -1.0f, rand() % 10 - 5)));
		bushesDrawable->AddTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5)));
		bushesDrawable->LinkShaderProgram(shaderPrograms[1]);

		this->AddDrawable(bushesDrawable);
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

void Scene::Render()
{
	this->cameraControll->KeyboardMovement();

 	for (int i = 0; i < this->drawables.size(); i++) {
		this->drawables[i]->Render();
	}
}