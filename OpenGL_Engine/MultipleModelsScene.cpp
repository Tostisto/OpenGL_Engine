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

	// Phong Textured Shader 
	VertexShader* texturedphongVertexShader = new VertexShader("Shaders\\texturedPhong.vert");
	FragmentShader* texturedPhongFragmentShader = new FragmentShader("Shaders\\texturedPhong.frag");
	ShaderProgram* texturedPhongShaderProgram = new ShaderProgram(texturedphongVertexShader, texturedPhongFragmentShader, ShaderType::TEXTURED_PHONG);
	AddShaderProgram(texturedPhongShaderProgram);

	AddCubeMap();

	Camera* camera = new Camera();

	CameraControll* cameraControll = new CameraControll(camera, window);

	AddCameraControll(cameraControll);

	AddWindow(window);
	AddCamera(camera);

	SpotLight* spotLight = new SpotLight(glm::vec3(2.0f, 2.0f, 0.0f), glm::vec3(0.914214f, -0.275637f, 0.297046f), glm::vec3(1.f, 1.f, 1.f), glm::cos(glm::radians(20.0f)));
	AddLight(spotLight);

	//PointLight* pointLight1 = new PointLight(glm::vec3(12.0f, 5.0f, 2.0f), glm::vec3(0.8f, 0.8f, 0.8f));
	//AddLight(pointLight1);


	// Tree model
	ModelLoader* texturedPlainObjModel = new ModelLoader("C:\\Users\\kubac\\Desktop\\models\\plane.obj", ModelLoadType::TEXTURES);

	Model* texturedPlainModel = new Model(texturedPlainObjModel->getVertices(), texturedPlainObjModel->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* texturedPlainDrawable = new DrawableModel(texturedPlainModel);
	texturedPlainDrawable->AddTransformation(new Translation(glm::vec3(0.0f, -1.0f, 0.0f)));
	texturedPlainDrawable->AddTransformation(new Scale(100));
	texturedPlainDrawable->LinkShaderProgram(texturedPhongShaderProgram);
	texturedPlainDrawable->SetMaterialTexture(new Texture("Textures\\grass.png"));

	this->AddDrawable(texturedPlainDrawable);

	// Model 1
	ModelLoader* modelLoader = new ModelLoader("Models\\jeep.obj", ModelLoadType::NO_TEXTURES);

	Model* model = new Model(modelLoader->getVertices(), modelLoader->getVerticesSize()/6, ModelType::NO_TEXTURE_MODEL);
	DrawableModel* drawable = new DrawableModel(model);
	drawable->AddTransformation(new Translation(glm::vec3(5.0f, -0.6f, -5.0f)));
	drawable->AddTransformation(new Rotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	drawable->AddTransformation(new Scale(0.35f));
	drawable->SetMaterial(new Material(
		glm::vec3(0.03f, 0.03f, 0.03f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	drawable->LinkShaderProgram(lambertShaderProgram);

	this->AddDrawable(drawable);

	//// Tree model
	//Model* treeModel = new Model(tree, 92814, ModelType::NO_TEXTURE_MODEL);

	//for (int i = 0; i < 20; i++)
	//{
	//	DrawableModel* treeDrawable = new DrawableModel(treeModel);
	//	treeDrawable->AddTransformation(new Translation(glm::vec3(rand() % 15 - 5, -1.0f, rand() % 15 - 5)));
	//	treeDrawable->AddTransformation(new Scale(0.5f));
	//	treeDrawable->AddTransformation(new Rotation(rand() % 360, glm::vec3(0.0f, 1.0f, 0.0f)));
	//	treeDrawable->LinkShaderProgram(phongShaderProgram);
	//	treeDrawable->SetMaterial(new Material(
	//		glm::vec3(0.05, 0.2f, 0.05f),
	//		glm::vec3(1.0f, 1.0f, 1.0f), 
	//		glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)
	//	);

	//	this->AddDrawable(treeDrawable);
	//}

	//// Bushes model
	//Model* bushesModel = new Model(bushes, 8730, ModelType::NO_TEXTURE_MODEL);

	//// 100 bushers on plain with random position
	//for (int i = 0; i < 100; i++)
	//{
	//	DrawableModel* bushesDrawable = new DrawableModel(bushesModel);
	//	bushesDrawable->AddTransformation(new Translation(glm::vec3(rand() % 15 - 5, -1.0f, rand() % 15 - 5)));
	//	bushesDrawable->AddTransformation(new Scale(0.5f));
	//	bushesDrawable->AddTransformation(new Rotation(rand() % 360, glm::vec3(0.0f, 1.0f, 0.0f)));
	//	bushesDrawable->LinkShaderProgram(phongShaderProgram);
	//	bushesDrawable->SetMaterial(new Material(
	//		glm::vec3(0.1f, 0.35f, 0.1f), 
	//		glm::vec3(1.0f, 1.0f, 1.0f), 
	//		glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)
	//	);

	//	this->AddDrawable(bushesDrawable);
	//}

	//// 10 gift boxes on plain with random position
	//Model* giftBoxModel = new Model(gift, 66624, ModelType::NO_TEXTURE_MODEL);
	//
	//for (int i = 0; i < 10; i++)
	//{
	//	DrawableModel* giftBoxDrawable = new DrawableModel(giftBoxModel);
	//	giftBoxDrawable->AddTransformation(new Translation(glm::vec3(rand() % 15 - 5, -1.0f, rand() % 15 - 5)));
	//	giftBoxDrawable->AddTransformation(new Rotation(rand() % 360, glm::vec3(0.0f, 1.0f, 0.0f)));
	//	giftBoxDrawable->SetMaterial(new Material(
	//		glm::vec3(0.1f, 0.1f, 0.1f), 
	//		glm::vec3(1.0f, 1.0f, 1.0f), 
	//		glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)
	//	);
	//	giftBoxDrawable->LinkShaderProgram(phongShaderProgram);
	//	this->AddDrawable(giftBoxDrawable); 
	//}

	// House model 1
	ModelLoader* houseModelLoader = new ModelLoader("C:\\Users\\kubac\\Desktop\\models\\003_obj.obj", ModelLoadType::TEXTURES);

	Model* houseModel = new Model(houseModelLoader->getVertices(), houseModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* houseDrawable = new DrawableModel(houseModel);
	houseDrawable->AddTransformation(new Translation(glm::vec3(14.0f, -0.95f, 0.0f)));
	houseDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	houseDrawable->AddTransformation(new Scale(0.5f));
	houseDrawable->SetMaterial(new Material(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	houseDrawable->SetMaterialTexture(new Texture("C:\\Users\\kubac\\Desktop\\models\\003_diffuse.png"));
	houseDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(houseDrawable);


	// House model 1
	ModelLoader* houseModelLoader2 = new ModelLoader("C:\\Users\\kubac\\Desktop\\models\\model.obj", ModelLoadType::TEXTURES);

	Model* houseModel2 = new Model(houseModelLoader2->getVertices(), houseModelLoader2->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* houseDrawable2 = new DrawableModel(houseModel2);
	houseDrawable2->AddTransformation(new Translation(glm::vec3(20.0f, -0.9f, 10.0f)));
	houseDrawable2->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	houseDrawable2->AddTransformation(new Scale(0.5f));
	houseDrawable2->SetMaterial(new Material(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	houseDrawable2->SetMaterialTexture(new Texture("C:\\Users\\kubac\\Desktop\\models\\test.png"));
	houseDrawable2->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(houseDrawable2);


	// Zombie model
	ModelLoader* zombieModelLoader = new ModelLoader("C:\\Users\\kubac\\Desktop\\models\\zombie.obj", ModelLoadType::TEXTURES);

	Model* zombieModel = new Model(zombieModelLoader->getVertices(), zombieModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* zombieDrawable = new DrawableModel(zombieModel);
	zombieDrawable->AddTransformation(new Translation(glm::vec3(0.0f, -0.9f, 0.0f)));
	zombieDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	zombieDrawable->AddTransformation(new Scale(0.5f));
	zombieDrawable->SetMaterial(new Material(
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		256.0f
	));
	zombieDrawable->SetMaterialTexture(new Texture("C:\\Users\\kubac\\Desktop\\models\\zombie.png"));
	zombieDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(zombieDrawable);


}