#pragma once

#include <vector>
#include "DrawableModel.h"
#include "Translation.h"

class ModelsManipulation
{
private:
	std::vector<DrawableModel*>* drawables;

	Model* model;
	ShaderProgram* shaderProgram;

public:
	ModelsManipulation(std::vector<DrawableModel*>* drawables);

	DrawableModel* GetModel(int id);
	void RemoveModel(int id);

	void AddDrawableModel(Model* model, ShaderProgram* shaderProgram);

	void AddModel(glm::vec3 position);
};

