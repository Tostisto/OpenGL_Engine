#pragma once

#include "Scene.h"
#include "models.h"

class MultipleModelsScene : public Scene
{
public:
	MultipleModelsScene(Window* window);
	void Create() override;
};

