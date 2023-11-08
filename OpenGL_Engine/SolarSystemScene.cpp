#include "SolarSystemScene.h"

glm::vec3 SolarSystemScene::MoveOnLine(DrawableModel* object, glm::vec3 position, glm::vec3 toPosition, float speed)
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

	Model* sphereModel = new Model(sphere, 2880, 6, ModelType::NO_TEXTURE_MODEL);

	// Sun Drawable
	sun = new DrawableModel(sphereModel);
	sun->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	sun->LinkShaderProgram(lambertShaderProgram);
	sun->AddTransformation(new Scale(glm::vec3(5.0, 5.0, 5.0)));
	sun->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	sun->SetMaterial(new Material(glm::vec3(1.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), 32.0));
	this->AddDrawable(sun);

	// Mercury Drawable
	mercury = new DrawableModel(sphereModel);
	mercury->LinkShaderProgram(lambertShaderProgram);

	mercury->AddTransformation(new Scale(glm::vec3(0.7, 0.7, 0.7)));
	mercury->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	mercury->AddTransformation(new Rotation(0.1f, glm::vec3(0.0f, 1.0f, 0.0f), 0.01f));
	mercury->AddTransformation(new Translation(glm::vec3(10.0, 0.0, 0.0)));

	mercury->SetMaterial(new Material(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));
	this->AddDrawable(mercury);

	// Venus Drawable
	venus = new DrawableModel(sphereModel);
	venus->LinkShaderProgram(lambertShaderProgram);

	mercury->AddTransformation(new Scale(glm::vec3(0.85, 0.85, 0.85)));
	venus->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	venus->AddTransformation(new Rotation(0.1f, glm::vec3(0.0f, 1.0f, 0.0f), 0.02f));
	venus->AddTransformation(new Translation(glm::vec3(14.0, 0.0, 0.0)));

	venus->SetMaterial(new Material(glm::vec3(0.7, 0.3, 0.3), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));
	this->AddDrawable(venus);

	// Earth Drawable
	earth = new DrawableModel(sphereModel);
	earth->LinkShaderProgram(lambertShaderProgram);

	TransformCollection* planetTransformCollection = new TransformCollection();
	planetTransformCollection->addTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	planetTransformCollection->addTransformation(new Rotation(0.1f, glm::vec3(0.0f, 1.0f, 0.0f), 0.02f));
	planetTransformCollection->addTransformation(new Translation(glm::vec3(20.0, 0.0, 0.0)));

	earth->AddTranformationCollection(planetTransformCollection);

	earth->SetMaterial(new Material(glm::vec3(0.3, 1.0, 3.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));
	this->AddDrawable(earth);

	// Earth Moon Drawable
	moon = new DrawableModel(sphereModel);
	moon->LinkShaderProgram(phongShaderProgram);
	moon->AddTranformationCollection(planetTransformCollection);

	TransformCollection* moonTransformCollection = new TransformCollection();
	moonTransformCollection->addTransformation(new Scale(glm::vec3(0.3, 0.3, 0.3)));
	moonTransformCollection->addTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	moonTransformCollection->addTransformation(new Rotation(0.1f, glm::vec3(0.0f, 1.0f, 0.0f), 0.10f));
	moonTransformCollection->addTransformation(new Translation(glm::vec3(8.0, 0.0, 0.0)));
		
	moon->AddTranformationCollection(moonTransformCollection);

	this->AddDrawable(moon);


	// Mars Drawable
	mars = new DrawableModel(sphereModel);
	mars->LinkShaderProgram(lambertShaderProgram);
	
	mars->AddTransformation(new Scale(glm::vec3(0.9, 0.9, 0.9)));
	mars->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	mars->AddTransformation(new Rotation(0.1f, glm::vec3(0.0f, 1.0f, 0.0f), 0.014f));
	mars->AddTransformation(new Translation(glm::vec3(27.0, 0.0, 0.0)));

	mars->SetMaterial(new Material(glm::vec3(0.6, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));
	this->AddDrawable(mars);

	// Jupiter Drawable
	jupiter = new DrawableModel(sphereModel);
	jupiter->LinkShaderProgram(lambertShaderProgram);

	jupiter->AddTransformation(new Scale(glm::vec3(1.5, 1.5, 1.5)));
	jupiter->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	jupiter->AddTransformation(new Rotation(0.1f, glm::vec3(0.0f, 1.0f, 0.0f), 0.013f));
	jupiter->AddTransformation(new Translation(glm::vec3(40.0, 0.0, 0.0)));

	jupiter->SetMaterial(new Material(glm::vec3(0.5, 0.5, 0.5), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));

	this->AddDrawable(jupiter);

	// Saturn Drawable
	saturn = new DrawableModel(sphereModel);
	saturn->LinkShaderProgram(lambertShaderProgram);

	saturn->AddTransformation(new Scale(glm::vec3(1.2, 1.2, 1.2)));
	saturn->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	saturn->AddTransformation(new Rotation(0.1f, glm::vec3(0.0f, 1.0f, 0.0f), 0.017f));
	saturn->AddTransformation(new Translation(glm::vec3(50.0, 0.0, 0.0)));

	saturn->SetMaterial(new Material(glm::vec3(0.3, 0.5, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));

	this->AddDrawable(saturn);

	// Uranus Drawable
	uranus = new DrawableModel(sphereModel);
	uranus->LinkShaderProgram(lambertShaderProgram);

	uranus->AddTransformation(new Scale(glm::vec3(1.0, 1.0, 1.0)));
	uranus->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	uranus->AddTransformation(new Rotation(0.1f, glm::vec3(0.0f, 1.0f, 0.0f), 0.024f));
	uranus->AddTransformation(new Translation(glm::vec3(60.0, 0.0, 0.0)));

	uranus->SetMaterial(new Material(glm::vec3(0.3, 1.0, 3.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));

	this->AddDrawable(uranus);

	// Neptune Drawable
	neptune = new DrawableModel(sphereModel);
	neptune->LinkShaderProgram(lambertShaderProgram);

	neptune->AddTransformation(new Scale(glm::vec3(1.0, 1.0, 1.0)));
	neptune->AddTransformation(new Translation(glm::vec3(0.0, 0.0, 0.0)));
	neptune->AddTransformation(new Rotation(0.1f, glm::vec3(0.0f, 1.0f, 0.0f), 0.012f));
	neptune->AddTransformation(new Translation(glm::vec3(70.0, 0.0, 0.0)));

	neptune->SetMaterial(new Material(glm::vec3(0.3, 1.0, 3.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 32.0));

	this->AddDrawable(neptune);	
}	