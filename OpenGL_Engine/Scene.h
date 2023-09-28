#pragma once

#include <vector>
#include "Drawable.h"

#include "Model.h"
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"


class Scene
{
private:
	std::vector<Drawable*> drawables;
	std::vector<ShaderProgram*> shaderPrograms;

public:
	Scene();

	void AddDrawable(Drawable* drawable);
	void RemoveDrawable(Drawable* drawable);

	void Render();
};

