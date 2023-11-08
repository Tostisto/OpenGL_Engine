#include "Texture.h"

Texture::Texture(const char* texturePath)
{
 	this->textureID = SOIL_load_OGL_texture(texturePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
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
