#include "Scene.h"

Scene::Scene()
{
	this->drawables = std::vector<Drawable*>();

	float points[] = {
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f,1.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,1.0f
	};

	Model* model = new Model(points, 3, 6);

	Drawable* drawable = new Drawable(model);

	this->AddDrawable(drawable);

	VertexShader* vertexShaderTest = new VertexShader("Shaders\\shader.vert");
	FragmentShader* fragmentShaderTest = new FragmentShader("Shaders\\shader.frag");

	ShaderProgram* shaderProgram = new ShaderProgram(vertexShaderTest, fragmentShaderTest);

	this->shaderPrograms.push_back(shaderProgram);

	float cubeVertices[] = {
		// Front face
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

		// Back face
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

		// Top face
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

		// Right face
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		 // Left face
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	};

	Model* model2 = new Model(cubeVertices, 36, 6);
	
	Drawable* drawable2 = new Drawable(model2);
	//this->AddDrawable(drawable2);

	FragmentShader* fragmentShaderTest2 = new FragmentShader("Shaders\\shader.frag");
	ShaderProgram* shaderProgram2 = new ShaderProgram(vertexShaderTest, fragmentShaderTest2);

	this->shaderPrograms.push_back(shaderProgram2);
}

void Scene::AddDrawable(Drawable* drawable)
{
	this->drawables.push_back(drawable);
}

void Scene::RemoveDrawable(Drawable* drawable)
{
	double angle = 20.0;

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

		this->drawables[i]->LinkShaderProgram(this->shaderPrograms[i]);

		float angleInRadians = static_cast<float>(glm::radians(angle));

		Rotation* rotation = new Rotation(angleInRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		Translation* translation = new Translation(glm::vec3(1.0f, 0.0f, 0.0f));
		Scale* scale = new Scale(glm::vec3(0.5f, 0.5f, 0.5f));

		TransformCollection* transformCollection = new TransformCollection();

		transformCollection->addTransformation(rotation);
		//transformCollection->addTransformation(translation);
		//transformCollection->addTransformation(scale);
		

		this->shaderPrograms[i]->setUniform("modelMatrix", transformCollection->getMatrix());

		this->angle += 0.5f;

		this->drawables[i]->Render();
	}
}
