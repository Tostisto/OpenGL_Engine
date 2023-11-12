#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "Model.h"
#include "ShaderProgram.h"
#include "Material.h"

class DrawableBase
{
protected:
	Model* model;
	ShaderProgram* shader_program = nullptr;

public:
	DrawableBase(Model* model);

	void LinkShaderProgram(ShaderProgram* shader_program);
	virtual void Render();
};

