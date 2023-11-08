#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "DrawableBase.h"
#include "Drawable.h"

#include "models.h"

class CubeMap : public Drawable
{
private:
	std::vector<const char*> faces;


public:
	CubeMap(std::vector<const char*> faces);
	CubeMap();

	void Render();
};

