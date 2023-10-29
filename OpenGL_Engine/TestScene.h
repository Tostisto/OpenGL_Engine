#pragma once

#include "Scene.h"
#include "models.h"

class TestScene : public Scene
{
public:
	TestScene() = default;
	void Create(Window* window) override;
};
