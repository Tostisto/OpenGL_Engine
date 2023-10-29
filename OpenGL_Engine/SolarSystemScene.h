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

	glm::vec3 meteoritPos = glm::vec3(0.0, 10.0, 10.0);
	glm::vec3 oldMeteoritPosition = glm::vec3(0.0f, 0.0f, 0.0f);


	glm::vec3 MoveOnLine(Drawable* object, glm::vec3 position, glm::vec3 toPosition, float speed);

public:
	SolarSystemScene() = default;
	void Create(Window* window) override;	
	void UpdateFrame() override;
};

