#include "Scene.h"

Scene::Scene()
{
	this->drawables = std::vector<Drawable*>();

	float points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	   -0.5f, -0.5f, 0.0f
	};

	Model* model = new Model(points, 3);

	Drawable* drawable = new Drawable(model);

	this->AddDrawable(drawable);

	VertexShader* vertexShaderTest = new VertexShader("Shaders\\shader.vert");
	FragmentShader* fragmentShaderTest = new FragmentShader("Shaders\\shader.frag");

	ShaderProgram* shaderProgram = new ShaderProgram(vertexShaderTest, fragmentShaderTest);

	this->shaderPrograms.push_back(shaderProgram);
}

void Scene::AddDrawable(Drawable* drawable)
{
	this->drawables.push_back(drawable);
}

void Scene::RemoveDrawable(Drawable* drawable)
{
	for (int i = 0; i < this->drawables.size(); i++) {
		if (this->drawables[i] == drawable) {
			this->drawables.erase(this->drawables.begin() + i);
			return;
		}
	}
}

void Scene::Render()
{
	for (int i = 0; i < this->drawables.size(); i++) {
		
		this->drawables[i]->LinkShaderProgram(this->shaderPrograms[0]);

		this->drawables[i]->Render();
	}
}
