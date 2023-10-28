#include "PhongTestScene.h"


void PhongTestScene::Create(Window* window)
{
	// Phong Shader 
	VertexShader* phongVertexShader = new VertexShader("Shaders\\phong.vert");
	FragmentShader* phongFragmentShader = new FragmentShader("Shaders\\phong.frag");
	ShaderProgram* phongShaderProgram = new ShaderProgram(phongVertexShader, phongFragmentShader, "phongShaderProgram");
	AddShaderProgram(phongShaderProgram);

	Camera* camera = new Camera();
	Light* light = new Light();

	CameraControll* cameraControll = new CameraControll(camera, window);

	AddCameraControll(cameraControll);

	AddCamera(camera);
	AddLight(light);
	AddWindow(window);

	light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	light->setColor(glm::vec3(1.0f, 1.0f, 1.0f));


	Model* model = new Model(sphere, 2880, 6);
	
	Drawable* drawable1 = new Drawable(model);
	drawable1->AddTransformation(new Translation(glm::vec3(2.0, -2.0, 0.0)));
	drawable1->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable1);


	Drawable* drawable2 = new Drawable(model);
	drawable2->AddTransformation(new Translation(glm::vec3(2.0, 2.0, 0.0)));
	drawable2->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable2);


	Drawable* drawable3 = new Drawable(model);
	drawable3->AddTransformation(new Translation(glm::vec3(-2.0, 2.0, 0.0)));
	drawable3->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable3);

	Drawable* drawable4 = new Drawable(model);
	drawable4->AddTransformation(new Translation(glm::vec3(-2.0, -2.0, 0.0)));
	drawable4->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable4);
}
