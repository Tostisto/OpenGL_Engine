#pragma once

#include "Scene.h"
#include "models.h"

class SolarSystemScene : public Scene
{
private:
	DrawableModel* sun;

	DrawableModel* mercury;
	DrawableModel* venus;
	DrawableModel* earth;
	DrawableModel* mars;
	DrawableModel* jupiter;
	DrawableModel* saturn;
	DrawableModel* uranus;
	DrawableModel* neptune;

	DrawableModel* moon;

	glm::vec3 MoveOnLine(DrawableModel* object, glm::vec3 position, glm::vec3 toPosition, float speed);

	float angle = 0.0f;

public:
	SolarSystemScene() = default;
	void Create(Window* window) override;	
};

