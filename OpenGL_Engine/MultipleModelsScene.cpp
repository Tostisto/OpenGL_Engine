#include "MultipleModelsScene.h"

MultipleModelsScene::MultipleModelsScene(Window* window) : Scene(window) {}

void MultipleModelsScene::Create()
{
	// Cube Map
	AddCubeMap(std::vector<const char*> {
		"Textures\\Skybox\\dark\\right.png",
		"Textures\\Skybox\\dark\\left.png",
		"Textures\\Skybox\\dark\\top.png",
		"Textures\\Skybox\\dark\\bottom.png",
		"Textures\\Skybox\\dark\\front.png",
		"Textures\\Skybox\\dark\\back.png"
	}
	
	);

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

	PointLight* pointLight1 = new PointLight(glm::vec3(12.0f, 20.0f, -25.0f), glm::vec3(0.8f, 0.8f, 0.8f), new LightAttenuation(1.0, 0.01, 0.0035));
	AddLight(pointLight1);

	// Terrain model
	DrawableModel* texturedTerrainDrawable = new DrawableModel("Models\\tor_terrain\\tor.obj", "Models\\tor_terrain\\tor_texture.jpeg", this->ModelsCount());
	texturedTerrainDrawable->LinkShaderProgram(texturedPhongShaderProgram);
	texturedTerrainDrawable->AddTransformation(new Translation(glm::vec3(0.0f, 40.0f, 0.0f)));
	texturedTerrainDrawable->setRemoveable(false);
	this->AddDrawable(texturedTerrainDrawable);

	// House model 1
	DrawableModel* houseDrawable = new DrawableModel("Models\\old_house\\old_house.obj", "Models\\old_house\\old_house.png", this->ModelsCount());
	houseDrawable->AddTransformation(new Translation(glm::vec3(7.28f, -3.2f, -25.14f)));
	houseDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	houseDrawable->AddTransformation(new Scale(0.5f));
	houseDrawable->SetMaterial(new Material(
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f
	));
	houseDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(houseDrawable);

	// Well model
	ModelLoader* wellModelLoader = new ModelLoader("Models\\well\\well.obj", ModelLoadType::TEXTURES);

	Model* wellModel = new Model(wellModelLoader->getVertices(), wellModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);
	DrawableModel* wellDrawable = new DrawableModel(wellModel, this->ModelsCount());
	wellDrawable->AddTransformation(new Translation(glm::vec3(15.0f, -2.5f, 1.0f)));
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
	DrawableModel* mediavalHouseDrawable = new DrawableModel(mediavalHouseModel, this->ModelsCount());
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

	// Mediaval house drawable 2
	DrawableModel* mediavalHouseDrawable2 = new DrawableModel(mediavalHouseModel, this->ModelsCount());
	mediavalHouseDrawable2->AddTransformation(new Translation(glm::vec3(5.0f, -2.0f, -5.0f)));
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
	DrawableModel* mediavalSmallHouseDrawable = new DrawableModel("Models\\mediaval_small_house\\mediaval_small_house.obj", "Models\\mediaval_small_house\\mediaval_small_house.png", this->ModelsCount());
	mediavalSmallHouseDrawable->AddTransformation(new Translation(glm::vec3(15.0f, -0.17f, 10.0f)));
	mediavalSmallHouseDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	mediavalSmallHouseDrawable->AddTransformation(new Scale(0.5f));
	mediavalSmallHouseDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(mediavalSmallHouseDrawable);

	// Church model
	DrawableModel* churchDrawable = new DrawableModel("Models\\church\\church.obj", "Models\\church\\church.png", this->ModelsCount());
	churchDrawable->AddTransformation(new Translation(glm::vec3(16.5f, -2.8f, -8.6f)));
	churchDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	churchDrawable->AddTransformation(new Scale(0.5f));
	churchDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(churchDrawable);


	// Zombie model
	ModelLoader* zombieModelLoader = new ModelLoader("Models\\zombie\\zombie.obj", ModelLoadType::TEXTURES);
	Model* zombieModel = new Model(zombieModelLoader->getVertices(), zombieModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);

	AddModelPickers(zombieModel, texturedPhongShaderProgram);
}