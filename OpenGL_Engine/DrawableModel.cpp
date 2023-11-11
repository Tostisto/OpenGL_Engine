#include "DrawableModel.h"

DrawableModel::DrawableModel(Model* model) : DrawableBase(model)
{
	this->transformation_collection = new TransformCollection();
}

void DrawableModel::AddTransformation(Transformation* transformation)
{
	this->transformation_collection->addTransformation(transformation);
}

void DrawableModel::AddTranformationCollection(TransformCollection* transformation_collection)
{
	this->transformation_collection->addTransformationCollection(transformation_collection);
}

void DrawableModel::SetMaterial(Material* material)
{
	this->material = material;
}

void DrawableModel::SetMaterialTexture(Texture* texture)
{
	if (this->material == nullptr)
	{
		this->material = new Material(
			glm::vec3(0.1f, 0.1f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			32.0f
		);
		fprintf(stderr, "WARNING: Drawable::SetMaterialTexture() called before material was set. Using default material\n");
	}

	this->material->SetTexture(texture);
}

void DrawableModel::Render()
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
		this->shader_program->setUniform("modelMatrix", this->transformation_collection->transform());


		if (this->shader_program->shaderType == ShaderType::TEXTURE || this->shader_program->shaderType == ShaderType::TEXTURED_PHONG)
		{
			this->material->GetTexture()->BindTexture();

			this->shader_program->setUniform("textureUnitID", 1);
		}


		if (this->shader_program->shaderType == ShaderType::PHONG ||
			this->shader_program->shaderType == ShaderType::BLINN_PHONG ||
			this->shader_program->shaderType == ShaderType::TEXTURED_PHONG)
		{
			this->shader_program->setUniform("material.ambient", this->material->GetAmbient());
			this->shader_program->setUniform("material.diffuse", this->material->GetDiffuse());
			this->shader_program->setUniform("material.specular", this->material->GetSpecular());
			this->shader_program->setUniform("material.shininess", this->material->GetShininess());
		}
		else if (this->shader_program->shaderType == ShaderType::LAMBERT)
		{
			this->shader_program->setUniform("material.ambient", this->material->GetAmbient());
			this->shader_program->setUniform("material.diffuse", this->material->GetDiffuse());
		}

		this->model->Draw();
	}
}