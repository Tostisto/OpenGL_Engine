#include "Drawable.h"

Drawable::Drawable(Model* model)
{
	this->transformation_collection = new TransformCollection();
	this->model = model;
}

void Drawable::LinkShaderProgram(ShaderProgram* shader_program)
{
	this->shader_program = shader_program;
}

void Drawable::AddTransformation(Transformation* transformation)
{
	this->transformation_collection->addTransformation(transformation);
}

void Drawable::SetMaterial(Material* material)
{
	this->material = material;
}

void Drawable::Render()
{
	if (this->shader_program == nullptr) {
		fprintf(stderr, "ERROR: Drawable::Render() called before shader program was linked. Shader program is required for rendering\n");
		exit(EXIT_FAILURE);
	}
	else if (this->material == nullptr)
	{

		this->material = new Material(
			glm::vec3(0.1f, 0.1f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			32.0f
		);

		fprintf(stderr, "WARNING: Drawable::Render() called before material was set. Using default material\n");
	}
	else {
 		this->shader_program->UseProgram();
		this->shader_program->setUniform("modelMatrix", this->transformation_collection->getMatrix());

		// if shader type is phong
		if (strcmp(this->shader_program->ShaderType, "phongShaderProgram") == 0 || strcmp(this->shader_program->ShaderType, "blinnShaderProgram") == 0)
		{
			this->shader_program->setUniform("material.ambient", this->material->GetAmbient());
			this->shader_program->setUniform("material.diffuse", this->material->GetDiffuse());
			this->shader_program->setUniform("material.specular", this->material->GetSpecular());
			this->shader_program->setUniform("material.shininess", this->material->GetShininess());
		}
		else if (strcmp(this->shader_program->ShaderType, "lambertShaderProgram") == 0)
		{
			this->shader_program->setUniform("material.ambient", this->material->GetAmbient());
			this->shader_program->setUniform("material.diffuse", this->material->GetDiffuse());
		}

		this->model->Draw();
	}
}