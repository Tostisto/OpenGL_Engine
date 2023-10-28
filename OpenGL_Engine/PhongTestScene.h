#pragma once

#include "Scene.h"
#include "models.h"

class PhongTestScene : public Scene
{
public:
	PhongTestScene() = default;
	void Create(Window* window) override;
};

