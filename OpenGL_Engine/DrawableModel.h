#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>

#include "DrawableBase.h"

#include "Model.h"
#include "ShaderProgram.h"

#include "Material.h"
#include "TransformCollection.h"

#include "ModelLoader.h"

class DrawableModel : public DrawableBase
{
private:
	TransformCollection* transformation_collection = nullptr;

protected:
	Material* material = nullptr;
	Texture* texture = nullptr;

public:
	DrawableModel(Model* model);
	DrawableModel(const char* model_path, const char* texture_path);
	DrawableModel(const char* model_path, const char* texture_path, Material* material);
	DrawableModel(Model* model, Material* material, const char* texture_path);

	void AddTransformation(Transformation* transformation);
	void AddTranformationCollection(TransformCollection* transformation_collection);
	void SetMaterial(Material* material);
	void SetMaterialTexture(Texture* texture);
	void Render() override;
};