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

	int modelId	= -1;

	bool removeable = true;

protected:
	Material* material = nullptr;
	Texture* texture = nullptr;

public:
	DrawableModel(Model* model, int modelId);
	DrawableModel(const char* model_path, const char* texture_path, int modelId);
	DrawableModel(const char* model_path, const char* texture_path, Material* material, int modelId);
	DrawableModel(Model* model, Material* material, const char* texture_path, int modelId);

	void setRemoveable(bool removeable);
	bool IsRemoveable();

	void AddTransformation(Transformation* transformation);
	void AddTranformationCollection(TransformCollection* transformation_collection);
	void SetMaterial(Material* material);
	void SetMaterialTexture(Texture* texture);
	int GetModelId();
	void Render() override;
};