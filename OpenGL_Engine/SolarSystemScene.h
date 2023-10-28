#pragma once

#include "Scene.h"
#include "models.h"

class SolarSystemScene : public Scene
{
private:
	Drawable* planet;
	Drawable* moon;

public:
	SolarSystemScene() = default;
	void Create(Window* window) override;
	void UpdateFrame() override;
};

