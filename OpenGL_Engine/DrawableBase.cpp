#include "DrawableBase.h"

DrawableBase::DrawableBase(Model* model)
{
	this->model = model;
}

void DrawableBase::LinkShaderProgram(ShaderProgram* shader_program)
{
	this->shader_program = shader_program;
}

void DrawableBase::Render()
{
	if (this->shader_program == nullptr) {
		fprintf(stderr, "ERROR: Drawable::Render() called before shader program was linked. Shader program is required for rendering\n");
		exit(EXIT_FAILURE);
	}

	this->model->Draw();
}
