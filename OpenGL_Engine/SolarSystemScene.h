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

	float angle = 0.0f;

public:
	SolarSystemScene(Window* window);
	void Create() override;
};

