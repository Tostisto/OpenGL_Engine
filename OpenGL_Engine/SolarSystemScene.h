#pragma once

#include "Scene.h"
#include "models.h"

class SolarSystemScene : public Scene
{
private:
	Drawable* planet;
	Drawable* planet2;
	Drawable* planet3;
	Drawable* moon;
	Drawable* meteorit;

	glm::vec3 oldPlanetPosition = glm::vec3(0.0f, 0.0f, 0.0f);
public:
	SolarSystemScene() = default;
	void Create(Window* window) override;
	void UpdateFrame() override;
};

