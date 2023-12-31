#include "Texture.h"

Texture::Texture(const char* texturePath)
{
	this->textureID = SOIL_load_OGL_texture(texturePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Repeat textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (this->textureID == 0)
	{
		fprintf(stderr, "SOIL loading error: '%s'\n", SOIL_last_result());
		exit(EXIT_FAILURE);
	}
}

Texture::Texture(std::vector<const char*> faces)
{
	glActiveTexture(GL_TEXTURE0);

	this->textureID = SOIL_load_OGL_cubemap(
		faces[0],
		faces[1],
		faces[2],
		faces[3],
		faces[4],
		faces[5],
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);

	if (this->textureID == 0)
	{
		fprintf(stderr, "SOIL loading error: '%s'\n", SOIL_last_result());
		exit(EXIT_FAILURE);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

GLuint Texture::GetTextureID()
{
	return this->textureID;
}

void Texture::BindTexture()
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}