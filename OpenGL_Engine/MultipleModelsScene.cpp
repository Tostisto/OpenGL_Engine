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

	PointLight* pointLight1 = new PointLight(glm::vec3(12.0f, 5.0f, 2.0f), glm::vec3(0.8f, 0.8f, 0.8f));
	AddLight(pointLight1);

	// Terrain model
	ModelLoader* texturedPlainObjModel = new ModelLoader("Models\\plane\\plane.obj", ModelLoadType::TEXTURES);

	Model* texturedPlainModel = new Model(texturedPlainObjModel->getVertices(), texturedPlainObjModel->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* texturedPlainDrawable = new DrawableModel(texturedPlainModel);
	texturedPlainDrawable->AddTransformation(new Translation(glm::vec3(0.0f, -1.0f, 0.0f)));
	texturedPlainDrawable->AddTransformation(new Scale(100));
	texturedPlainDrawable->LinkShaderProgram(texturedPhongShaderProgram);
	texturedPlainDrawable->SetMaterialTexture(new Texture("Models\\plane\\grass.png"));

	this->AddDrawable(texturedPlainDrawable);


	// House model 1
	ModelLoader* houseModelLoader = new ModelLoader("Models\\old_house\\old_house.obj", ModelLoadType::TEXTURES);

	Model* houseModel = new Model(houseModelLoader->getVertices(), houseModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* houseDrawable = new DrawableModel(houseModel);
	houseDrawable->AddTransformation(new Translation(glm::vec3(15.0f, -0.95f, -10.0f)));
	houseDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	houseDrawable->AddTransformation(new Scale(0.5f));
	houseDrawable->SetMaterial(new Material(
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	houseDrawable->SetMaterialTexture(new Texture("Models\\old_house\\old_house.png"));
	houseDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(houseDrawable);


	// Zombie model
	ModelLoader* zombieModelLoader = new ModelLoader("Models\\zombie\\zombie.obj", ModelLoadType::TEXTURES);

	Model* zombieModel = new Model(zombieModelLoader->getVertices(), zombieModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* zombieDrawable = new DrawableModel(zombieModel);
	zombieDrawable->AddTransformation(new Translation(glm::vec3(10.0f, -0.9f, -10.0f)));
	zombieDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	zombieDrawable->AddTransformation(new Scale(0.5f));
	zombieDrawable->SetMaterial(new Material(
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		256.0f
	));
	zombieDrawable->SetMaterialTexture(new Texture("Models\\zombie\\zombie.png"));
	zombieDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(zombieDrawable);


	// Well model
	ModelLoader* wellModelLoader = new ModelLoader("Models\\well\\well.obj", ModelLoadType::TEXTURES);

	Model* wellModel = new Model(wellModelLoader->getVertices(), wellModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* wellDrawable = new DrawableModel(wellModel);
	wellDrawable->AddTransformation(new Translation(glm::vec3(15.0f, -1.35f, 1.0f)));
	wellDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	wellDrawable->AddTransformation(new Scale(0.5f));
	wellDrawable->SetMaterial(new Material(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	wellDrawable->SetMaterialTexture(new Texture("Models\\well\\well.png"));
	wellDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(wellDrawable);


	// Mediaval house model
	ModelLoader* mediavalHouseModelLoader = new ModelLoader("Models\\medieval_house\\medieval_house.obj", ModelLoadType::TEXTURES);

	Model* mediavalHouseModel = new Model(mediavalHouseModelLoader->getVertices(), mediavalHouseModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* mediavalHouseDrawable = new DrawableModel(mediavalHouseModel);
	mediavalHouseDrawable->AddTransformation(new Translation(glm::vec3(5.0f, -0.95f, 5.0f)));
	mediavalHouseDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	mediavalHouseDrawable->AddTransformation(new Scale(0.5f));
	mediavalHouseDrawable->SetMaterial(new Material(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	mediavalHouseDrawable->SetMaterialTexture(new Texture("Models\\medieval_house\\medieval_house.png"));
	mediavalHouseDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(mediavalHouseDrawable);

	// Mediaval small house drawable 2
	DrawableModel* mediavalHouseDrawable2 = new DrawableModel(mediavalHouseModel);
	mediavalHouseDrawable2->AddTransformation(new Translation(glm::vec3(5.0f, -0.95f, -5.0f)));
	mediavalHouseDrawable2->AddTransformation(new Rotation(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	mediavalHouseDrawable2->AddTransformation(new Scale(0.5f));
	mediavalHouseDrawable2->SetMaterial(new Material(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	mediavalHouseDrawable2->SetMaterialTexture(new Texture("Models\\medieval_house\\medieval_house.png"));
	mediavalHouseDrawable2->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(mediavalHouseDrawable2);


	// Mediaval small house model
	ModelLoader* mediavalSmallHouseModelLoader = new ModelLoader("Models\\mediaval_small_house\\mediaval_small_house.obj", ModelLoadType::TEXTURES);

	Model* testModel = new Model(mediavalSmallHouseModelLoader->getVertices(), mediavalSmallHouseModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* mediavalSmallHouseDrawable = new DrawableModel(testModel);
	mediavalSmallHouseDrawable->AddTransformation(new Translation(glm::vec3(15.0f, -0.95f, 10.0f)));
	mediavalSmallHouseDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	mediavalSmallHouseDrawable->AddTransformation(new Scale(0.5f));
	mediavalSmallHouseDrawable->SetMaterial(new Material(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	mediavalSmallHouseDrawable->SetMaterialTexture(new Texture("Models\\mediaval_small_house\\mediaval_small_house.png"));
	mediavalSmallHouseDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(mediavalSmallHouseDrawable);


	// Church model
	ModelLoader* churchModelLoader = new ModelLoader("Models\\church\\church.obj", ModelLoadType::TEXTURES);

	Model* churchModel = new Model(churchModelLoader->getVertices(), churchModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* churchDrawable = new DrawableModel(churchModel);
	churchDrawable->AddTransformation(new Translation(glm::vec3(18.0f, -0.95f, -8.0f)));
	churchDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	churchDrawable->AddTransformation(new Scale(0.5f));
	churchDrawable->SetMaterial(new Material(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	churchDrawable->SetMaterialTexture(new Texture("Models\\church\\church.png"));
	churchDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(churchDrawable);
}