#include "LightAttenuation.h"

LightAttenuation::LightAttenuation()
{
	this->constant = 1.0f;
	this->linear = 0.0f;
	this->quadratic = 0.0f;
}

LightAttenuation::LightAttenuation(float constant, float linear, float quadratic)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

LightAttenuation::~LightAttenuation() {}

float LightAttenuation::getConstant()
{
	return this->constant;
}

float LightAttenuation::getLinear()
{
	return this->linear;
}

float LightAttenuation::getQuadratic()
{
	return this->quadratic;
}

void LightAttenuation::setConstant(float constant)
{
	this->constant = constant;
}

void LightAttenuation::setLinear(float linear)
{
	this->linear = linear;
}

void LightAttenuation::setQuadratic(float quadratic)
{
	this->quadratic = quadratic;
}
