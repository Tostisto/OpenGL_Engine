#include "BezierCubic.h"

BezierCubic::BezierCubic(float t, const glm::mat4x3& control_points)
{
	this->t = t;
	this->delta = 0.005f;
	this->control_points = control_points;

	this->M = glm::mat4(
		glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
		glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
		glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)
	);
}

glm::vec3 BezierCubic::getPoint(float t)
{
	glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);

	glm::vec3 p = parameters * M * glm::transpose(control_points);

	return p;
}