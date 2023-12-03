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
	});

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

	PointLight* mainPointLight = new PointLight(glm::vec3(12.0f, 20.0f, -25.0f), glm::vec3(0.8f, 0.8f, 0.8f), new LightAttenuation(1.0, 0.01, 0.0035));
	AddLight(mainPointLight);

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


	DrawableModel* balloonDrawable = new DrawableModel("Models\\Balloon\\balloon.obj", "Models\\Balloon\\balloon.png", this->ModelsCount());
	balloonDrawable->LinkShaderProgram(texturedPhongShaderProgram);
	balloonDrawable->AddTransformation(new BezierMove(new BezierCurve(std::vector<glm::vec3>{
		glm::vec3(-16.377647, 12.720327, -1.732411),
		glm::vec3(-11.267562, 10.232153, 0.807765),
		glm::vec3(-3.089642, 7.052194, 1.363671),
		glm::vec3(4.042195, 6.434549, 1.488161),

		glm::vec3(16.144655, 5.920825, -1.967085),
		glm::vec3(16.713919, 4.941939, 0.852805),
		glm::vec3(6.959396, 10.148960, 12.064244),

		glm::vec3(15.441535, 11.425210, 24.246193),
		glm::vec3(22.248676, 12.598897, 24.126078),
		glm::vec3(28.778481, 10.499387, 9.287327),

		glm::vec3(32.861008, 5.679283, 6.358057),
		glm::vec3(33.171082, 2.176871, -12.400961),
		glm::vec3(23.368048, 9.869701, -26.660786),

		glm::vec3(8.170578, 6.606007, -26.394661),
		glm::vec3(-10.015809, 9.811376, -16.222879),
		glm::vec3(-16.377647, 12.720327, -1.732411),
	})));

	balloonDrawable->AddTransformation(new Scale(0.5f));

	this->AddDrawable(balloonDrawable);

	// Lamp model
	DrawableModel* lampDrawable = new DrawableModel("Models\\Lamp\\lamp.obj", "Models\\Lamp\\lamp.png", this->ModelsCount());
	lampDrawable->AddTransformation(new Translation(glm::vec3(9.556348, 0.609612, 7.927305)));
	lampDrawable->AddTransformation(new Rotation(glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	lampDrawable->AddTransformation(new Scale(0.1f));

	lampDrawable->LinkShaderProgram(texturedPhongShaderProgram);

	this->AddDrawable(lampDrawable);

	PointLight* lampLight = new PointLight(glm::vec3(9.976400, 1.299655, 7.682962), glm::vec3(0.8f, 0.8f, 0.8f), new LightAttenuation(1.0, 0.2, 0.2));
	AddLight(lampLight);


	// Tree model
	ModelLoader* treeModelLoader = new ModelLoader("Models\\tree\\tree.obj", ModelLoadType::TEXTURES);
	Model* treeModel = new Model(treeModelLoader->getVertices(), treeModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);

	std::vector<glm::vec3> treePos = {
		glm::vec3(18.504757, -0.104064, 8.066108),
		glm::vec3(22.175293, -0.586600, 7.644120),
		glm::vec3(26.185909, -0.005345, 9.557009),
		glm::vec3(27.157824, -1.084487, 5.894264),
		glm::vec3(33.734344, -0.974613, 8.044823),
		glm::vec3(30.876213, -1.821315, 3.432981),
		glm::vec3(39.534779, -1.700815, 5.503481),
		glm::vec3(-6.179501, -0.392948, 4.072983),
		glm::vec3(-6.410388, -1.159166, -0.677454),
		glm::vec3(11.588986, 0.829395, 12.453218),
		glm::vec3(9.922670, 0.989205, 12.235650),
		glm::vec3(7.852908, 0.875060, 12.452591),
		glm::vec3(12.696671, -3.306732, -27.561201),
		glm::vec3(-0.609988, -2.950706, -20.309269),
		glm::vec3(-6.436823, -2.369847, -11.198640),
		glm::vec3(21.665222, -2.995471, -13.818957),
		glm::vec3(26.059561, -3.328746, -16.488533),
		glm::vec3(23.779718, -3.758565, -24.337551),
		glm::vec3(17.042479, -3.535051, -25.085442),
		glm::vec3(19.227848, -3.373455, -18.797901),
		glm::vec3(11.122137, -3.413140, -20.423431),
		glm::vec3(12.807762, -3.238789, -17.052355),
		glm::vec3(12.525364, -2.814675, -13.168715),
		glm::vec3(9.225514, -2.106660, -10.352777),
		glm::vec3(5.989227, -2.424416, -11.782846),
		glm::vec3(10.651567, -3.025081, -16.254183),
		glm::vec3(22.546810, 2.100646, 23.115002),
		glm::vec3(26.441414, 2.176115, 22.943401),
		glm::vec3(31.062437, 1.399057, 19.293667),
		glm::vec3(35.335266, -0.157658, 11.321941),
		glm::vec3(30.835377, -0.082877, 11.512963),
		glm::vec3(28.672882, -0.040692, 10.923083),
		glm::vec3(28.479029, -0.875404, 7.189468),
		glm::vec3(32.664642, -1.584874, 4.908153),
		glm::vec3(34.229568, -0.789246, 8.704112),
		glm::vec3(36.209114, -0.707188, 9.312837),
		glm::vec3(38.326637, -1.281597, 7.596889),
		glm::vec3(35.912193, -2.051858, 3.167134),
		glm::vec3(36.090427, -2.673460, -0.448103),
		glm::vec3(39.725899, -2.479726, 0.098725),
		glm::vec3(40.178223, -1.531739, 5.931637),
		glm::vec3(42.926838, -0.972652, 7.971371)
	};

	for (int i = 0; i < treePos.size(); i++) {
		DrawableModel* treeDrawable = new DrawableModel(treeModel, this->ModelsCount());
		treeDrawable->AddTransformation(new Translation(treePos[i]));
		treeDrawable->AddTransformation(new Scale(0.25f));

		// random rotation on y axis
		float randomRotation = (float)(rand() % 360);
		treeDrawable->AddTransformation(new Rotation(glm::radians(randomRotation), glm::vec3(0.0f, 1.0f, 0.0f)));

		treeDrawable->LinkShaderProgram(texturedPhongShaderProgram);
		treeDrawable->SetMaterialTexture(new Texture("Models\\tree\\tree.png"));

		this->AddDrawable(treeDrawable);
	}


	// Zombie model
	ModelLoader* zombieModelLoader = new ModelLoader("Models\\zombie\\zombie.obj", ModelLoadType::TEXTURES);
	Model* zombieModel = new Model(zombieModelLoader->getVertices(), zombieModelLoader->getVerticesSize() / 8, ModelType::TEXTURE_MODEL);

	AddModelPickers(zombieModel, texturedPhongShaderProgram);
}