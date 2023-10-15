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

void Drawable::Render()
{
	if (this->shader_program == nullptr) {
		fprintf(stderr, "ERROR: Drawable::Render() called before shader program was linked\n");
		exit(EXIT_FAILURE);
	}
	else {
 		this->shader_program->UseProgram();
		this->shader_program->setUniform("modelMatrix", this->transformation_collection->getMatrix());
		this->model->Draw();
	}
}