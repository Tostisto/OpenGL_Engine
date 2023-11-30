#include "BezierMoveScene.h"

BezierMoveScene::BezierMoveScene(Window* window) : Scene(window) {}

void BezierMoveScene::Create()
{
	// Lambert Shader 
	VertexShader* lamberVertexShader = new VertexShader("Shaders\\lambert.vert");
	FragmentShader* lamberFragmentShader = new FragmentShader("Shaders\\lambert.frag");
	ShaderProgram* lambertShaderProgram = new ShaderProgram(lamberVertexShader, lamberFragmentShader, ShaderType::LAMBERT);
	AddShaderProgram(lambertShaderProgram);

	PointLight* pointLight1 = new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f), new LightAttenuation(1.0, 0.01, 0.0035));
	AddLight(pointLight1);

	// Sphere model
	Model* model = new Model(suziFlat, 2904, ModelType::NO_TEXTURE_MODEL);
	DrawableModel* sphere = new DrawableModel(model, this->ModelsCount());

	sphere->AddTransformation(new BezierMove(new BezierCurve(std::vector<glm::vec3>{
		glm::vec3(0, 0, 0),
		glm::vec3(2, 2, 0),
		glm::vec3(4, 2, 0),
		glm::vec3(6, 0, 0),
		glm::vec3(8, -2, 0),
		glm::vec3(10, 0, 0),
		glm::vec3(12, 4, 0),
	})));

	sphere->AddTransformation(new Scale(0.5f));

	sphere->LinkShaderProgram(lambertShaderProgram);

	this->AddDrawable(sphere);
}