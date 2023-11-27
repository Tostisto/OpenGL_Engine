#pragma once
#include "Scene.h"

class BezierMoveScene : public Scene
{
public:
	BezierMoveScene(Window* window);
	void Create() override;
};
