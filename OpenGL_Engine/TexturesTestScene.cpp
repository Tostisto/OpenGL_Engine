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

	Model* triangleModel = new Model(triangle, 6, ModelType::TEXTURE_MODEL);

	DrawableModel* triangleDrawable = new DrawableModel(triangleModel);
	triangleDrawable->LinkShaderProgram(textureShaderProgram);
	triangleDrawable->SetMaterialTexture(new Texture("Textures\\grass.png"));

	this->AddDrawable(triangleDrawable);

	DrawableModel* triangleDrawable2 = new DrawableModel(triangleModel);
	triangleDrawable2->LinkShaderProgram(textureShaderProgram);
	triangleDrawable2->SetMaterialTexture(new Texture("Textures\\wooden_fence.png"));
	triangleDrawable2->AddTransformation(new Translation(glm::vec3(0.0f, 0.0f, -2.0f)));
	triangleDrawable2->AddTransformation(new Rotation(20.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	triangleDrawable2->AddTransformation(new Scale(2.5f));

	this->AddDrawable(triangleDrawable2);
}
