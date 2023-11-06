#include "TexturesTestScene.h"

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

	AddCameraControll(cameraControll);

	AddWindow(window);
	AddCamera(camera);


	// Plain model
	Model* plainModel = new Model(plain, 6, 6);
	Drawable* plainDrawable = new Drawable(plainModel);
	plainDrawable->AddTransformation(new Translation(glm::vec3(0.0f, -1.0f, 0.0f)));
	plainDrawable->AddTransformation(new Scale(glm::vec3(100.0f, 1.0f, 100.0f)));
	plainDrawable->LinkShaderProgram(constantShaderProgram);

	this->AddDrawable(plainDrawable);


	// Plain model
	Model* triangleModel = new Model(triangle, 6, 8, true);
	Drawable* triangleDrawable = new Drawable(triangleModel);
	triangleDrawable->LinkShaderProgram(textureShaderProgram);
	triangleDrawable->SetMaterialTexture(new Texture("C:\\Users\\kubac\\Desktop\\textures\\grass.png"));

	this->AddDrawable(triangleDrawable);
}
