#include "Scene.h"

#include "sphere.h"
#include "suzi_smooth.h"

Scene::Scene(Window* window)
{
	this->window = window;

	this->drawables = std::vector<Drawable*>();

	// Model 1
	Model* model = new Model(sphere, 2880, 6);
	Drawable* drawable = new Drawable(model);

	this->AddDrawable(drawable);

	// Model 1 Shaders
	VertexShader* vertexShaderTest = new VertexShader("Shaders\\shader.vert");
	FragmentShader* fragmentShaderTest = new FragmentShader("Shaders\\shader.frag");
	ShaderProgram* shaderProgram = new ShaderProgram(vertexShaderTest, fragmentShaderTest);

	this->shaderPrograms.push_back(shaderProgram);



	//// Model 2
	//Model* model2 = new Model(suziSmooth, 2904, 6);
	//Drawable* drawable2 = new Drawable(model2);

	//this->AddDrawable(drawable2);

	//// Model 2 Shaders
	//VertexShader* vertexShaderTest2 = new VertexShader("Shaders\\shader.vert");
	//FragmentShader* fragmentShaderTest2 = new FragmentShader("Shaders\\shader.frag");
	//ShaderProgram* shaderProgram2 = new ShaderProgram(vertexShaderTest2, fragmentShaderTest2);

	//this->shaderPrograms.push_back(shaderProgram2);



	this->camera = new Camera();
	this->camera->Attach(shaderProgram);

	this->cameraControll = new CameraControll(this->camera, this->window);
	Callback::GetInstance()->Attach(this->cameraControll);
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

	glm::mat4 projectionMatrix = this->window->GetProjectionMatrix();

	this->drawables[0]->LinkShaderProgram(this->shaderPrograms[0]);
		
	// First object transformations
	float angleInRadians1 = static_cast<float>(glm::radians(20.0));
	Rotation* rotation1 = new Rotation(angleInRadians1, glm::vec3(1.0f, 1.0f, 1.0f));
	Translation* translation1 = new Translation(glm::vec3(-0.5f, 0.0f, 0.0f));
	Scale* scale1 = new Scale(glm::vec3(0.5f, 0.5f, 0.5f));

	TransformCollection* transformationCollection1 = new TransformCollection();
	transformationCollection1->addTransformation(rotation1);
	transformationCollection1->addTransformation(translation1);
	transformationCollection1->addTransformation(scale1);


	this->shaderPrograms[0]->setUniform("modelMatrix", transformationCollection1->getMatrix());

	this->shaderPrograms[0]->setUniform("projectionMatrix", projectionMatrix);

	this->drawables[0]->Render();





	//this->drawables[1]->LinkShaderProgram(this->shaderPrograms[1]);

	//// Second object transformations
	//float angleInRadians2 = static_cast<float>(glm::radians(50.0));
	//Rotation* rotation2 = new Rotation(angleInRadians2, glm::vec3(1.0f, 1.0f, 1.0f));
	//Translation* translation2 = new Translation(glm::vec3(0.3f, 0.0f, 0.0f));
	//Scale* scale2 = new Scale(glm::vec3(0.5f, 0.5f, 0.5f));

	//TransformCollection* tranformationCollection2 = new TransformCollection();
	//tranformationCollection2->addTransformation(rotation2);
	//tranformationCollection2->addTransformation(translation2);
	//tranformationCollection2->addTransformation(scale2);

	//this->shaderPrograms[1]->setUniform("modelMatrix", tranformationCollection2->getMatrix());

	//// test projection and view matrix
	//this->shaderPrograms[1]->setUniform("projectionMatrix", projectionMatrix);

	//this->drawables[1]->Render();
}
