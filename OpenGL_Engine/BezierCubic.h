#pragma once

#include <glm/glm.hpp>

class BezierCubic
{
private: 
	glm::mat4 M;
	float t;
	float delta;
	glm::mat4x3 control_points;

public:
	BezierCubic(float t, const glm::mat4x3& control_points);

	glm::vec3 getPoint(float t);
};

