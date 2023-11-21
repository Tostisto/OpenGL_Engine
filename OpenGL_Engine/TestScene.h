#pragma once

#include "Scene.h"
#include "models.h"

class TestScene : public Scene
{
public:
	TestScene(Window* window);
	void Create() override;
};
