#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SOIL.h>
#include <GL/glew.h>
#include <vector>

class Texture
{
private:
	GLuint textureID;

public:
	Texture(const char* texturePath);				// 2D Texture	
	Texture(std::vector<const char*> faces);		// CubeMap Texture

	GLuint GetTextureID();

	void BindTexture();
};

