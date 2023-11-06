#pragma once

#include <glm/glm.hpp>
#include "Texture.h"

class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	Texture* texture;

public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

	void SetAmbient(glm::vec3 ambient);
	void SetDiffuse(glm::vec3 diffuse);
	void SetSpecular(glm::vec3 specular);
	void SetShininess(float shininess);
	void SetTexture(Texture* texture);

	glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();
	glm::vec3 GetSpecular();
	Texture* GetTexture();

	float GetShininess();
};