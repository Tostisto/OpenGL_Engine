#pragma once
class LightAttenuation
{
private:
	float constant;
	float linear;
	float quadratic;

public:
	LightAttenuation();
	LightAttenuation(float constant, float linear, float quadratic);
	~LightAttenuation();

	float getConstant();
	float getLinear();
	float getQuadratic();

	void setConstant(float constant);
	void setLinear(float linear);
	void setQuadratic(float quadratic);
};

