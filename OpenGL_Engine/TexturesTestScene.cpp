#include "TexturesTestScene.h"
#include "CubeMap.h"

void TexturesTestScene::Create(Window* window)
{
	// Constant Shader
	VertexShader* constantVertexShader = new VertexShader("Shaders\\constant.vert");
	FragmentShader* constantFragmentShader = new FragmentShader("Shaders\\constant.frag");
	ShaderProgram* constantShaderProgram = new ShaderProgram(constantVertexShader, constantFragmentShader, ShaderType::CONSTANT);
	AddShaderProgram(constantShaderProgram);

	// texture shader 
	VertexShader* textureVertexShader = new VertexShader("Shaders\\texture.vert");
	FragmentShader* textureFragmentShader = new FragmentShader("Shaders\\texture.frag");
	ShaderProgram* textureShaderProgram = new ShaderProgram(textureVertexShader, textureFragmentShader, ShaderType::TEXTURE);
	AddShaderProgram(textureShaderProgram);

	Camera* camera = new Camera();
	CameraControll* cameraControll = new CameraControll(camera, window);

 	AddCubeMap();

	AddCameraControll(cameraControll);

	AddWindow(window);
	AddCamera(camera);

	//// Plain model
	//Model* plainModel = new Model(plain, 6, 6, ModelType::NO_TEXTURE_MODEL);
	//Drawable* plainDrawable = new Drawable(plainModel);
	//plainDrawable->AddTransformation(new Translation(glm::vec3(0.0f, -1.0f, 0.0f)));
	//plainDrawable->AddTransformation(new Scale(glm::vec3(100.0f, 1.0f, 100.0f)));
	//plainDrawable->LinkShaderProgram(constantShaderProgram);

	//this->AddDrawable(plainDrawable);


	Model* triangleModel = new Model(triangle, 6, 8, ModelType::TEXTURE_MODEL);

	DrawableModel* triangleDrawable = new DrawableModel(triangleModel);
	triangleDrawable->LinkShaderProgram(textureShaderProgram);
	triangleDrawable->SetMaterialTexture(new Texture("Textures\\grass.png"));

	this->AddDrawable(triangleDrawable);


	DrawableModel* triangleDrawable2 = new DrawableModel(triangleModel);
	triangleDrawable2->LinkShaderProgram(textureShaderProgram);
	triangleDrawable2->SetMaterialTexture(new Texture("Textures\\wooden_fence.png"));
	triangleDrawable2->AddTransformation(new Translation(glm::vec3(0.0f, 0.0f, -2.0f)));
	triangleDrawable2->AddTransformation(new Rotation(20.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	triangleDrawable2->AddTransformation(new Scale(glm::vec3(2.5f, 2.5f, 2.5f)));

	this->AddDrawable(triangleDrawable2);

}
