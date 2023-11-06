#pragma once

#include "Scene.h"
#include "models.h"

class SolarSystemScene : public Scene
{
private:
	Drawable* sun;

	Drawable* mercury;
	Drawable* venus;
	Drawable* earth;
	Drawable* mars;
	Drawable* jupiter;
	Drawable* saturn;
	Drawable* uranus;
	Drawable* neptune;

	Drawable* moon;

	glm::vec3 MoveOnLine(Drawable* object, glm::vec3 position, glm::vec3 toPosition, float speed);

	float angle = 0.0f;

public:
	SolarSystemScene() = default;
	void Create(Window* window) override;	
};

