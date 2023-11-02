#include "MultipleModelsScene.h"


void MultipleModelsScene::Create(Window* window)
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

	CameraControll* cameraControll = new CameraControll(camera, window);

	AddCameraControll(cameraControll);

	AddWindow(window);
	AddCamera(camera);


	SpotLight* spotLight = new SpotLight(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f), glm::cos(glm::radians(30.0f)));
	AddLight(spotLight);

	PointLight* pointLight = new PointLight(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f));
	AddLight(pointLight);


	// Plain model
	Model* plainModel = new Model(plain, 6, 6);
	Drawable* plainDrawable = new Drawable(plainModel);
	plainDrawable->AddTransformation(new Translation(glm::vec3(0.0f, -1.0f, 0.0f)));
	plainDrawable->AddTransformation(new Scale(glm::vec3(10.0f, 1.0f, 10.0f)));
	plainDrawable->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(plainDrawable);

	// Model 1
	ModelLoader* modelLoader = new ModelLoader("Models\\jeep.obj");

	Model* model = new Model(modelLoader->getVertices(), modelLoader->getVerticesSize()/6, 6);
	Drawable* drawable = new Drawable(model);
	drawable->AddTransformation(new Translation(glm::vec3(5.0f, -0.6f, -5.0f)));
	drawable->AddTransformation(new Rotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	drawable->AddTransformation(new Scale(glm::vec3(0.35f, 0.35f, 0.35f)));
	drawable->SetMaterial(new Material(
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	drawable->LinkShaderProgram(phongShaderProgram);

	this->AddDrawable(drawable);

	// Tree model
	Model* treeModel = new Model(tree, 92814, 6);

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
	Model* bushesModel = new Model(bushes, 8730, 6);

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
	Model* giftBoxModel = new Model(gift, 66624, 6);
	
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
}
