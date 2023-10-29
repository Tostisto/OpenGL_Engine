#pragma once

#include "Scene.h"
#include "models.h"

class MultipleModelsScene : public Scene
{
public:
	MultipleModelsScene() = default;
	void Create(Window* window) override;
};

