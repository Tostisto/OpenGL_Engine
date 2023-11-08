#include "CubeMap.h"

CubeMap::CubeMap(std::vector<const char*> faces) : DrawableBase(new Model(skycube, 36, 3, ModelType::SKYBOX_MODEL))
{
	this->faces = faces;

	this->texture = new Texture(this->faces);
}

CubeMap::CubeMap() : DrawableBase(new Model(skycube, 36, 3, ModelType::SKYBOX_MODEL))
{
	std::vector<const char*> faces = {
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};

	this->faces = faces;

	this->texture = new Texture(this->faces);
}

void CubeMap::Render()
{
 	if (this->shader_program == nullptr) {
		fprintf(stderr, "ERROR: Drawable::Render() called before shader program was linked. Shader program is required for rendering\n");
		exit(EXIT_FAILURE);
	}

	this->shader_program->UseProgram();
	
	if (this->shader_program->shaderType == ShaderType::CUBEMAP)
	{
		this->shader_program->setUniform("textureUnitID", 0);
	}

	this->model->Draw();
}
