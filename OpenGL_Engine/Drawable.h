#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>

#include "DrawableBase.h"

#include "Model.h"
#include "ShaderProgram.h"

#include "Material.h"
#include "TransformCollection.h"

class Drawable : public DrawableBase
{
private:
	TransformCollection* transformation_collection = nullptr;

protected:
	Material* material = nullptr;

public:
	Drawable(Model* model);

	void AddTransformation(Transformation* transformation);
	void AddTranformationCollection(TransformCollection* transformation_collection);
	void SetMaterial(Material* material);
	void SetMaterialTexture(Texture* texture);
	void Render() override;
};