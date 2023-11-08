#include "PhongTestScene.h"


void PhongTestScene::Create(Window* window)
{
	// Phong Shader 
	VertexShader* phongVertexShader = new VertexShader("Shaders\\phong.vert");
	FragmentShader* phongFragmentShader = new FragmentShader("Shaders\\phong.frag");
	ShaderProgram* phongShaderProgram = new ShaderProgram(phongVertexShader, phongFragmentShader, ShaderType::PHONG);
	AddShaderProgram(phongShaderProgram);

	Camera* camera = new Camera();
	PointLight* light = new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	CameraControll* cameraControll = new CameraControll(camera, window);

	AddCameraControll(cameraControll);

	AddCamera(camera);
	AddWindow(window);
	AddLight(light);

	Model* model = new Model(sphere, 2880, 6, ModelType::NO_TEXTURE_MODEL);
	
	// Ball 1
	Drawable* drawable1 = new Drawable(model);
	drawable1->AddTransformation(new Translation(glm::vec3(2.0, -2.0, 0.0)));
	drawable1->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable1);

	// Ball 2
	Drawable* drawable2 = new Drawable(model);
	drawable2->AddTransformation(new Translation(glm::vec3(2.0, 2.0, 0.0)));
	drawable2->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable2);

	// Ball 3
	Drawable* drawable3 = new Drawable(model);
	drawable3->AddTransformation(new Translation(glm::vec3(-2.0, 2.0, 0.0)));
	drawable3->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable3);

	// Ball 4
	Drawable* drawable4 = new Drawable(model);
	drawable4->AddTransformation(new Translation(glm::vec3(-2.0, -2.0, 0.0)));
	drawable4->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable4);
}
