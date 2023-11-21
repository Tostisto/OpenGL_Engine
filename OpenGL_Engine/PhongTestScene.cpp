#include "PhongTestScene.h"

PhongTestScene::PhongTestScene(Window* window) : Scene(window) {}

void PhongTestScene::Create()
{
	// Phong Shader 
	VertexShader* phongVertexShader = new VertexShader("Shaders\\phong.vert");
	FragmentShader* phongFragmentShader = new FragmentShader("Shaders\\phong.frag");
	ShaderProgram* phongShaderProgram = new ShaderProgram(phongVertexShader, phongFragmentShader, ShaderType::PHONG);
	AddShaderProgram(phongShaderProgram);

	PointLight* light = new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	AddLight(light);


	Model* model = new Model(sphere, 2880, ModelType::NO_TEXTURE_MODEL);
	
	// Ball 1
	DrawableModel* drawable1 = new DrawableModel(model, this->ModelsCount());
	drawable1->AddTransformation(new Translation(glm::vec3(2.0, -2.0, 0.0)));
	drawable1->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable1);

	// Ball 2
	DrawableModel* drawable2 = new DrawableModel(model, this->ModelsCount());
	drawable2->AddTransformation(new Translation(glm::vec3(2.0, 2.0, 0.0)));
	drawable2->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable2);

	// Ball 3
	DrawableModel* drawable3 = new DrawableModel(model, this->ModelsCount());
	drawable3->AddTransformation(new Translation(glm::vec3(-2.0, 2.0, 0.0)));
	drawable3->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable3);

	// Ball 4
	DrawableModel* drawable4 = new DrawableModel(model, this->ModelsCount());
	drawable4->AddTransformation(new Translation(glm::vec3(-2.0, -2.0, 0.0)));
	drawable4->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable4);
}
