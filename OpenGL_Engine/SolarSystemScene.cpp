#include "SolarSystemScene.h"

void SolarSystemScene::Create(Window* window)
{
	// Constant Shader
	VertexShader* constantVertexShader = new VertexShader("Shaders\\constant.vert");
	FragmentShader* constantFragmentShader = new FragmentShader("Shaders\\constant.frag");
	ShaderProgram* constantShaderProgram = new ShaderProgram(constantVertexShader, constantFragmentShader, "constantShaderProgram");
	AddShaderProgram(constantShaderProgram);

	// Lambert Shader 
	VertexShader* lamberVertexShader = new VertexShader("Shaders\\lambert.vert");
	FragmentShader* lamberFragmentShader = new FragmentShader("Shaders\\lambert.frag");
	ShaderProgram* lambertShaderProgram = new ShaderProgram(lamberVertexShader, lamberFragmentShader, "lambertShaderProgram");
	AddShaderProgram(lambertShaderProgram);

	// Phong Shader 
	VertexShader* phongVertexShader = new VertexShader("Shaders\\phong.vert");
	FragmentShader* phongFragmentShader = new FragmentShader("Shaders\\phong.frag");
	ShaderProgram* phongShaderProgram = new ShaderProgram(phongVertexShader, phongFragmentShader, "phongShaderProgram");
	AddShaderProgram(phongShaderProgram);

	// Blinn shader 
	VertexShader* blinnVertexShader = new VertexShader("Shaders\\blinn.vert");
	FragmentShader* blinnFragmentShader = new FragmentShader("Shaders\\blinn.frag");
	ShaderProgram* blinnShaderProgram = new ShaderProgram(blinnVertexShader, blinnFragmentShader, "blinnShaderProgram");
	AddShaderProgram(blinnShaderProgram);

	Camera* camera = new Camera();
	Light* light = new Light();

	CameraControll* cameraControll = new CameraControll(camera, window);

	AddCameraControll(cameraControll);

	AddCamera(camera);
	AddLight(light);
	AddWindow(window);

	light->setPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	light->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

	Model* sphereModel = new Model(sphere, 2880, 6);

	// Sun Drawable
	Drawable* sun = new Drawable(sphereModel);
	sun->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	sun->LinkShaderProgram(constantShaderProgram);

	this->AddDrawable(sun);

	// Planet Drawable
	planet = new Drawable(sphereModel);

	planet->LinkShaderProgram(lambertShaderProgram);
	planet->AddTransformation(new Translation(glm::vec3(5.0, 0.0, 0.0)));

	this->AddDrawable(planet);


	// Moon Drawable
	moon = new Drawable(sphereModel);
	moon->AddTransformation(new Translation(glm::vec3(8.0, 0.0, 0.0)));
	moon->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(moon);
}

void SolarSystemScene::UpdateFrame()
{
	// Rotate the planet around the sun
	planet->AddTransformation(new Translation(glm::vec3(-5.0, 0.0, 0.0)));
	planet->AddTransformation(new Rotation(0.1f, glm::vec3(0.0, 1.0, 0.0)));
	planet->AddTransformation(new Translation(glm::vec3(5.0, 0.0, 0.0)));
	
	moon->AddTransformation(new Translation(glm::vec3(-8.0, 0.0, 0.0)));
	moon->AddTransformation(new Rotation(0.2f, glm::vec3(0.0, 1.0, 0.0)));
	moon->AddTransformation(new Translation(glm::vec3(8.0, 0.0, 0.0)));


	moon->AddTransformation(new Translation(glm::vec3(-3.0, 0.0, 0.0)));
	moon->AddTransformation(new Rotation(0.2f, glm::vec3(0.0, 1.0, 0.0)));
	moon->AddTransformation(new Translation(glm::vec3(3.0, 0.0, 0.0)));
}
