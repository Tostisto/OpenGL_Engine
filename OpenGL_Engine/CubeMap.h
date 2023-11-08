#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "DrawableBase.h"
#include "DrawableModel.h"

#include "models.h"

class CubeMap : public DrawableBase
{
private:
	std::vector<const char*> faces;
	Texture* texture;

public:
	CubeMap(std::vector<const char*> faces);
	CubeMap();

	void Render() override;
};

