#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "BezierCubic.h"

class BezierCurve
{
private: 
	std::vector<glm::vec3> controlPoints;
	std::vector<BezierCubic> bezierCubics;

public:
	BezierCurve(std::vector<glm::vec3> controlPoints);

	glm::vec3 getPoint(float t);
	int getCubicsCount();

	int getControlPointCount();
};

