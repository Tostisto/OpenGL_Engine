#include "Scene.h"

#include "sphere.h"
#include "suzi_smooth.h"

Scene::Scene(Window* window)
{
	this->window = window;

	this->drawables = std::vector<Drawable*>();

	// Model 1 Shaders
	VertexShader* vertexShaderTest = new VertexShader("Shaders\\phong.vert");
	FragmentShader* fragmentShaderTest = new FragmentShader("Shaders\\phong.frag");
	ShaderProgram* shaderProgram = new ShaderProgram(vertexShaderTest, fragmentShaderTest);

	this->shaderPrograms.push_back(shaderProgram);

	ModelLoader* modelLoader = new ModelLoader("C:\\Users\\kubac\\Desktop\\model.obj");

	// Model 1
	Model* model = new Model(modelLoader->getVertices(), modelLoader->getVerticesSize()/6, 6);
	Drawable* drawable = new Drawable(model);
	drawable->AddTransformation(new Translation(glm::vec3(3.0f, 0.0f, 0.0f)));
	drawable->AddTransformation(new Rotation(static_cast<float>(glm::radians(50.0)), glm::vec3(1.0f, 1.0f, 1.0f)));
	drawable->AddTransformation(new Scale(glm::vec3(0.0004f, 0.0004f, 0.0004f)));
	drawable->LinkShaderProgram(shaderPrograms[0]);

	this->AddDrawable(drawable);


	// Model 2 Shaders
	VertexShader*  vertexShaderTest2 = new VertexShader("Shaders\\phong.vert");
	FragmentShader* fragmentShaderTest2 = new FragmentShader("Shaders\\phong.frag");
	ShaderProgram* shaderProgram2 = new ShaderProgram(vertexShaderTest, fragmentShaderTest);

	this->shaderPrograms.push_back(shaderProgram2);


	// Model 2
	Model* model2 = new Model(suziSmooth, 2904, 6);
	Drawable* drawable2 = new Drawable(model2);
	drawable2->AddTransformation(new Translation(glm::vec3(-3.0f, 0.0f, 0.0f)));
	drawable2->LinkShaderProgram(shaderPrograms[1]);

	this->AddDrawable(drawable2);


	// Model 3 Shaders
	VertexShader*  vertexShaderTest3 = new VertexShader("Shaders\\phong.vert");
	FragmentShader* fragmentShaderTest3 = new FragmentShader("Shaders\\phong.frag");
	ShaderProgram* shaderProgram3 = new ShaderProgram(vertexShaderTest3, fragmentShaderTest3);

	this->shaderPrograms.push_back(shaderProgram3);

	// Model 3
	Model* model3 = new Model(sphere, 2880, 6);
	Drawable* drawable3 = new Drawable(model3);
	drawable3->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	drawable3->LinkShaderProgram(shaderPrograms[2]);

	this->AddDrawable(drawable3);

	// Camera
	this->camera = new Camera();

	this->cameraControll = new CameraControll(this->camera, this->window);
	Callback::GetInstance()->Attach(this->cameraControll);

	this->camera->Attach(shaderProgram);
	this->camera->Attach(shaderProgram2);
	this->camera->Attach(shaderProgram3);


	// Projection matrix
	glm::mat4 projectionMatrix = this->window->GetProjectionMatrix();

	// Projection matrix to shaders
	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		this->shaderPrograms[i]->UseProgram();
		this->shaderPrograms[i]->setUniform("projectionMatrix", projectionMatrix);
	}


	for (int i = 0; i < this->shaderPrograms.size(); i++) {
		this->window->Attach(this->shaderPrograms[i]);
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