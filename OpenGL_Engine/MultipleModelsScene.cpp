#include "MultipleModelsScene.h"

void MultipleModelsScene::Create(Window* window)
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

	CameraControll* cameraControll = new CameraControll(camera, window);

	AddCameraControll(cameraControll);

	AddWindow(window);
	AddCamera(camera);

	SpotLight* spotLight = new SpotLight(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.8f, 0.6f, 0.6f), glm::cos(glm::radians(20.0f)));
	AddLight(spotLight);

	PointLight* pointLight1 = new PointLight(glm::vec3(-5.0f, 5.0f, 5.0f), glm::vec3(0.8f, 0.2f, 0.2f));
	AddLight(pointLight1);

	PointLight* pointLight2 = new PointLight(glm::vec3(5.0f, 5.0f, -5.0f), glm::vec3(0.2f, 0.2f, 0.8f));
	AddLight(pointLight2);

	// Plain model
	Model* plainModel = new Model(plain, 6, 6, ModelType::NO_TEXTURE_MODEL);
	Drawable* plainDrawable = new Drawable(plainModel);
	plainDrawable->AddTransformation(new Translation(glm::vec3(0.0f, -1.0f, 0.0f)));
	plainDrawable->AddTransformation(new Scale(glm::vec3(100.0f, 1.0f, 100.0f)));
	plainDrawable->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(plainDrawable);

	// Model 1
	ModelLoader* modelLoader = new ModelLoader("Models\\jeep.obj");

	Model* model = new Model(modelLoader->getVertices(), modelLoader->getVerticesSize()/6, 6, ModelType::NO_TEXTURE_MODEL);
	Drawable* drawable = new Drawable(model);
	drawable->AddTransformation(new Translation(glm::vec3(5.0f, -0.6f, -5.0f)));
	drawable->AddTransformation(new Rotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	drawable->AddTransformation(new Scale(glm::vec3(0.35f, 0.35f, 0.35f)));
	drawable->SetMaterial(new Material(
		glm::vec3(0.03f, 0.03f, 0.03f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	drawable->LinkShaderProgram(blinnShaderProgram);

	this->AddDrawable(drawable);

	// Tree model
	Model* treeModel = new Model(tree, 92814, 6, ModelType::NO_TEXTURE_MODEL);

	for (int i = 0; i < 20; i++)
	{
		Drawable* treeDrawable = new Drawable(treeModel);
		treeDrawable->AddTransformation(new Translation(glm::vec3(rand() % 15 - 5, -1.0f, rand() % 15 - 5)));
		treeDrawable->AddTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5)));
		treeDrawable->AddTransformation(new Rotation(rand() % 360, glm::vec3(0.0f, 1.0f, 0.0f)));
		treeDrawable->LinkShaderProgram(phongShaderProgram);
		treeDrawable->SetMaterial(new Material(
			glm::vec3(0.05, 0.2f, 0.05f),
			glm::vec3(1.0f, 1.0f, 1.0f), 
			glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)
		);

		this->AddDrawable(treeDrawable);
	}

	// Bushes model
	Model* bushesModel = new Model(bushes, 8730, 6, ModelType::NO_TEXTURE_MODEL);

	// 100 bushers on plain with random position
	for (int i = 0; i < 100; i++)
	{
		Drawable* bushesDrawable = new Drawable(bushesModel);
		bushesDrawable->AddTransformation(new Translation(glm::vec3(rand() % 15 - 5, -1.0f, rand() % 15 - 5)));
		bushesDrawable->AddTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5)));
		bushesDrawable->AddTransformation(new Rotation(rand() % 360, glm::vec3(0.0f, 1.0f, 0.0f)));
		bushesDrawable->LinkShaderProgram(phongShaderProgram);
		bushesDrawable->SetMaterial(new Material(
			glm::vec3(0.1f, 0.35f, 0.1f), 
			glm::vec3(1.0f, 1.0f, 1.0f), 
			glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)
		);

		this->AddDrawable(bushesDrawable);
	}

	// 10 gift boxes on plain with random position
	Model* giftBoxModel = new Model(gift, 66624, 6, ModelType::NO_TEXTURE_MODEL);
	
	for (int i = 0; i < 10; i++)
	{
		Drawable* giftBoxDrawable = new Drawable(giftBoxModel);
		giftBoxDrawable->AddTransformation(new Translation(glm::vec3(rand() % 15 - 5, -1.0f, rand() % 15 - 5)));
		giftBoxDrawable->AddTransformation(new Rotation(rand() % 360, glm::vec3(0.0f, 1.0f, 0.0f)));
		giftBoxDrawable->SetMaterial(new Material(
			glm::vec3(0.1f, 0.1f, 0.1f), 
			glm::vec3(1.0f, 1.0f, 1.0f), 
			glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)
		);
		giftBoxDrawable->LinkShaderProgram(phongShaderProgram);
		this->AddDrawable(giftBoxDrawable);
	}

	
	pointLight1->setPosition(glm::vec3(20.0f, 5.0f, -10.0f));

}