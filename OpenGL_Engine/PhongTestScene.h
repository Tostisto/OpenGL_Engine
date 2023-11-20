#pragma once

#include "Scene.h"
#include "models.h"

class PhongTestScene : public Scene
{
public:
	PhongTestScene(Window* window);
	void Create() override;
};

