#include "BezierMoveScene.h"

BezierMoveScene::BezierMoveScene(Window* window) : Scene(window) {}

void BezierMoveScene::Create()
{
	// Constant Shader
	VertexShader* constantVertexShader = new VertexShader("Shaders\\constant.vert");
	FragmentShader* constantFragmentShader = new FragmentShader("Shaders\\constant.frag");
	ShaderProgram* constantShaderProgram = new ShaderProgram(constantVertexShader, constantFragmentShader, ShaderType::CONSTANT);
	AddShaderProgram(constantShaderProgram);

	// Sphere model
	Model* model = new Model(sphere, 2880, ModelType::NO_TEXTURE_MODEL);
	DrawableModel* sphere = new DrawableModel(model, this->ModelsCount());
	sphere->AddTransformation(new BezierMove(0.5f, glm::mat4x3(
		glm::vec3(0, 0, 0),
		glm::vec3(2, 2, 0),
		glm::vec3(4, 4, 0),
		glm::vec3(6, 0, 0)
	)));
	sphere->AddTransformation(new Scale(0.5f));

	sphere->LinkShaderProgram(constantShaderProgram);
	this->AddDrawable(sphere);
}