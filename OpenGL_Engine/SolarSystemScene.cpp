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
	sun->LinkShaderProgram(lambertShaderProgram);
	sun->SetMaterial(new Material(glm::vec3(1.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), 32.0));
	this->AddDrawable(sun);

	// Sun 2 Drawable
	Drawable* sun2 = new Drawable(sphereModel);
	sun2->AddTransformation(new Translation(glm::vec3(0.0, 10.0, 0.0)));
	sun2->LinkShaderProgram(lambertShaderProgram);
	sun2->SetMaterial(new Material(glm::vec3(1.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), 32.0));
	this->AddDrawable(sun2);


	// Planet 1 Drawable
	planet = new Drawable(sphereModel);
	planet->LinkShaderProgram(lambertShaderProgram);
	planet->AddTransformation(new Translation(glm::vec3(5.0, 0.0, 0.0)));
	planet->SetMaterial(new Material(glm::vec3(0.3, 1.0, 3.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));
	this->AddDrawable(planet);

	// Planet 2 Drawable
	planet2 = new Drawable(sphereModel);
	planet2->LinkShaderProgram(lambertShaderProgram);
	planet2->AddTransformation(new Translation(glm::vec3(12.0, 0.0, 0.0)));
	planet2->SetMaterial(new Material(glm::vec3(0.3, 0.3, 1.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), 32.0));
	this->AddDrawable(planet2);

	// Planet 3 Drawable
	planet3 = new Drawable(sphereModel);
	planet3->LinkShaderProgram(lambertShaderProgram);
	planet3->AddTransformation(new Translation(glm::vec3(0.0, 10.0, 5.0)));
	planet3->SetMaterial(new Material(glm::vec3(0.3, 0.3, 1.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), 32.0));
	this->AddDrawable(planet3);


	// Meteorit Drawable
	meteorit = new Drawable(sphereModel);
	meteorit->LinkShaderProgram(lambertShaderProgram);
	meteorit->AddTransformation(new Scale(glm::vec3(0.5, 0.5, 0.5)));
	meteorit->AddTransformation(new Translation(glm::vec3(0.0, 10.0, 10.0)));
	meteorit->SetMaterial(new Material(glm::vec3(0.2, 0.2, 0.2), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));
	this->AddDrawable(meteorit);

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

	//static float planetAngle = 0.0f;
	//const float planetRotationSpeed = 0.1f;

	//planetAngle += planetRotationSpeed;

	//float planetRadius = 5.0f;
	//glm::vec3 planetPosition;
	//planetPosition.x = planetRadius * cos(planetAngle);
	//planetPosition.y = 0.0f;
	//planetPosition.z = planetRadius * sin(planetAngle);

	//fprintf(stdout, "Planet Position: %f, %f, %f\n", planetPosition.x, planetPosition.y, planetPosition.z);

	//// how position change
	//glm::vec3 planetPositionChange = planetPosition - oldPlanetPosition;

	//// move the moon to the same position as the planet
	////moon->AddTransformation(new Translation(planetPositionChange));

	//oldPlanetPosition = planetPosition;

	// Moon rotation
	moon->AddTransformation(new Translation(glm::vec3(-5.0, 0.0, 0.0)));
	moon->AddTransformation(new Rotation(0.1f, glm::vec3(0.0, 1.0, 0.0)));
	moon->AddTransformation(new Translation(glm::vec3(5.0, 0.0, 0.0)));

	// Planet 2 rotation
	planet2->AddTransformation(new Translation(glm::vec3(-12.0, 0.0, 0.0)));
	planet2->AddTransformation(new Rotation(0.1f, glm::vec3(0.0, 1.0, 0.0)));
	planet2->AddTransformation(new Translation(glm::vec3(12.0, 0.0, 0.0)));

	// Rotate Planet 3 around the sun 2
	planet3->AddTransformation(new Translation(glm::vec3(0.0, 0.0, -5.0)));
	planet3->AddTransformation(new Rotation(0.1f, glm::vec3(0.0, 1.0, 0.0)));
	planet3->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 5.0)));

	//// Meteorit movement
	//meteorit->AddTransformation(new Translation(glm::vec3(0.0, -0.01, -0.01)));

	
	meteoritPos = MoveOnLine(meteorit, meteoritPos, glm::vec3(0.0, 0.0, 0.0), 0.1f);

	fprintf(stdout, "Meteorit Position: %f, %f, %f\n", meteoritPos.x, meteoritPos.y, meteoritPos.z);
}
