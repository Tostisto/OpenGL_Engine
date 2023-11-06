#include "Texture.h"

Texture::Texture(const char* texturePath)
{
	fprintf(stdout, "Loading texture: %s\n", texturePath);

	glActiveTexture(GL_TEXTURE0);
 	this->textureID = SOIL_load_OGL_texture(texturePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (this->textureID == 0)
	{
		fprintf(stderr, "SOIL loading error: '%s'\n", SOIL_last_result());
		exit(EXIT_FAILURE);
	}
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}

GLuint Texture::GetTextureID()
{
	return this->textureID;
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}
