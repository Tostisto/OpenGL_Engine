#include "Drawable.h"

Drawable::Drawable(Model* model)
{
	this->model = model;
}

void Drawable::LinkShaderProgram(ShaderProgram* shader_program)
{
	this->shader_program = shader_program;
}

void Drawable::Render()
{
	if (this->shader_program == nullptr) {
		fprintf(stderr, "ERROR: Drawable::Render() called before shader program was linked\n");
		exit(EXIT_FAILURE);
	}
	else {
		this->shader_program->UseProgram();
		this->model->Draw();
	}
}