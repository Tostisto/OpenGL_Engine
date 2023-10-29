#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

void Material::SetAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

void Material::SetDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

void Material::SetSpecular(glm::vec3 specular)
{
	this->specular = specular;
}

void Material::SetShininess(float shininess)
{
	this->shininess = shininess;
}

glm::vec3 Material::GetAmbient()
{
	return ambient;
}

glm::vec3 Material::GetDiffuse()
{
	return diffuse;
}

glm::vec3 Material::GetSpecular()
{
	return specular;
}

float Material::GetShininess()
{
	return shininess;
}