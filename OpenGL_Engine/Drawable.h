#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>

#include "Model.h"
#include "ShaderProgram.h"

#include "Material.h"
#include "TransformCollection.h"

class Drawable
{
private:
	Model* model;
	ShaderProgram* shader_program = nullptr;
	TransformCollection* transformation_collection = nullptr;
	Material* material = nullptr;

public:
	Drawable(Model* model);

	void LinkShaderProgram(ShaderProgram* shader_program);
	void AddTransformation(Transformation* transformation);
	void AddTranformationCollection(TransformCollection* transformation_collection);
	void SetMaterial(Material* material);
	void SetMaterialTexture(Texture* texture);
	glm::mat4 GetModelMatrix();
	void Render();
};