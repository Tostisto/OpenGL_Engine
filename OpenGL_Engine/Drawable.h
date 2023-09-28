#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "Model.h"
#include "ShaderProgram.h"

class Drawable
{
private:
	Model* model;
	ShaderProgram* shader_program = nullptr;

	public:
		Drawable(Model* model);

		void LinkShaderProgram(ShaderProgram* shader_program);

		void Render();
};

