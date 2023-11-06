#include "SolarSystemScene.h"

glm::vec3 SolarSystemScene::MoveOnLine(Drawable* object, glm::vec3 position, glm::vec3 toPosition, float speed)
{
	glm::vec3 direction = toPosition - position;

	glm::vec3 newPosition = position + (direction * speed);

	glm::vec3 positionChange = newPosition - position;

	object->AddTransformation(new Translation(positionChange));

	return newPosition;
}

void SolarSystemScene::Create(Window* window)
{
	// Constant Shader
	VertexShader* constantVertexShader = new VertexShader("Shaders\\constant.vert");
	FragmentShader* constantFragmentShader = new FragmentShader("Shaders\\constant.frag");
	ShaderProgram* constantShaderProgram = new ShaderProgram(constantVertexShader, constantFragmentShader, ShaderType::CONSTANT);
	AddShaderProgram(constantShaderProgram);

	// Lambert Shader 
	VertexShader* lamberVertexShader = new VertexShader("Shaders\\lambert.vert");
	FragmentShader* lamberFragmentShader = new FragmentShader("Shaders\\lambert.frag");
	ShaderProgram* lambertShaderProgram = new ShaderProgram(lamberVertexShader, lamberFragmentShader, ShaderType::LAMBERT);
	AddShaderProgram(lambertShaderProgram);

	// Phong Shader 
	VertexShader* phongVertexShader = new VertexShader("Shaders\\phong.vert");
	FragmentShader* phongFragmentShader = new FragmentShader("Shaders\\phong.frag");
	ShaderProgram* phongShaderProgram = new ShaderProgram(phongVertexShader, phongFragmentShader, ShaderType::PHONG);
	AddShaderProgram(phongShaderProgram);

	// Blinn shader 
	VertexShader* blinnVertexShader = new VertexShader("Shaders\\blinn.vert");
	FragmentShader* blinnFragmentShader = new FragmentShader("Shaders\\blinn.frag");
	ShaderProgram* blinnShaderProgram = new ShaderProgram(blinnVertexShader, blinnFragmentShader, ShaderType::BLINN_PHONG);
	AddShaderProgram(blinnShaderProgram);

	Camera* camera = new Camera();
	PointLight* light = new PointLight(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	CameraControll* cameraControll = new CameraControll(camera, window);

	AddCameraControll(cameraControll);

	AddCamera(camera);
	AddWindow(window);
	
	AddLight(light);

	Model* sphereModel = new Model(sphere, 2880, 6);

	// Sun Drawable
	sun = new Drawable(sphereModel);
	sun->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	sun->LinkShaderProgram(lambertShaderProgram);
	sun->AddTransformation(new Translation(glm::vec3(2.0, 0.0, 0.0)));
	sun->SetMaterial(new Material(glm::vec3(1.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), 32.0));
	this->AddDrawable(sun);

	// Planet 1 Drawable
	planet = new Drawable(sphereModel);
	planet->LinkShaderProgram(lambertShaderProgram);
	planet->AddTransformation(new Translation(glm::vec3(10.0, 0.0, 0.0)));	
	planet->AddTransformation(new Rotation(angle, glm::vec3(0.0, 1.0, 0.0)));
	planet->SetMaterial(new Material(glm::vec3(0.3, 1.0, 3.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));
	this->AddDrawable(planet);

	// Moon Drawable
	moon = new Drawable(sphereModel);
	moon->LinkShaderProgram(phongShaderProgram);
	moon->AddTransformation(new RotationAroundModel(0.1f, 2.0f, glm::vec3(0.0, 1.0, 0.0), moon->GetModelMatrix(), planet));
	this->AddDrawable(moon);
}

void SolarSystemScene::UpdateFrame()
{
	//// Rotate the planet around the sun
	//planet->AddTransformation(new Translation(glm::vec3(-8.0, 0.0, 0.0)));
	//planet->AddTransformation(new Rotation(0.1f, glm::vec3(0.0, 1.0, 0.0)));
	//planet->AddTransformation(new Translation(glm::vec3(8.0, 0.0, 0.0)));

	//moon->AddTransformation(new RotationAroundModel(0.1f, 2.0f, glm::vec3(0.0, 1.0, 0.0), moon->GetModelMatrix(), planet));
}
	