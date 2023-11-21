#include "ModelsManipulation.h"

ModelsManipulation::ModelsManipulation(std::vector<DrawableModel*>* drawables)
{
	this->drawables = drawables;
}

DrawableModel* ModelsManipulation::GetModel(int id)
{
	for (int i = 0; i < this->drawables->size(); i++)
	{
		if (this->drawables->at(i)->GetModelId() == id)
		{
			return this->drawables->at(i);
		}
	}
}

void ModelsManipulation::RemoveModel(int id)
{
	for (int i = 0; i < this->drawables->size(); i++)
	{
		if (this->drawables->at(i)->GetModelId() == id)
		{
			this->drawables->erase(this->drawables->begin() + i);
			return;
		}
	}
}

void ModelsManipulation::AddDrawableModel(Model* model, ShaderProgram* shaderProgram)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
}

void ModelsManipulation::AddModel(glm::vec3 position)
{
	if (this->model == nullptr || this->shaderProgram == nullptr)
	{
		fprintf(stderr, "ERROR: Model or ShaderProgram not set\n");

		return;
	}

	DrawableModel* drawable = new DrawableModel(this->model, this->drawables->size() + 1);

	drawable->AddTransformation(new Translation(position));
	drawable->LinkShaderProgram(this->shaderProgram);
	drawable->SetMaterialTexture(new Texture("Models\\zombie\\zombie.png"));

	this->drawables->push_back(drawable);
}
