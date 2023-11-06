#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SOIL.h>
#include <GL/glew.h>

class Texture
{
private:
	GLuint textureID;

public:
	Texture(const char* texturePath);
	
	GLuint GetTextureID();

	void BindTexture();
};

