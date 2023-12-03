#include "BezierCurve.h"

BezierCurve::BezierCurve(std::vector<glm::vec3> controlPoints)
{
	if (controlPoints.size() < 4)
	{
		fprintf(stderr, "BezierCurve: Not enough control points\n");
		exit(EXIT_FAILURE);
	}

	bezierCubics.emplace_back(0.5f, glm::mat4x3(
		controlPoints[0],
		controlPoints[1],
		controlPoints[2],
		controlPoints[3]
	));

	for (size_t i = 4; i <= controlPoints.size() - 3; i += 3) {
		bezierCubics.emplace_back(0.5f, glm::mat4x3(
			controlPoints[i - 1],
			controlPoints[i],
			controlPoints[i + 1],
			controlPoints[i + 2]
		));
	}
}

glm::vec3 BezierCurve::getPoint(float t)
{
	if (t < 0.0f || t > 1.0f)
	{
		fprintf(stderr, "BezierCurve: t must be between 0 and 1\n");
		exit(EXIT_FAILURE);
	}

	float segmentCount = static_cast<float>(bezierCubics.size());
	float segment = t * segmentCount;

	int selectedSegment = static_cast<int>(floor(segment));
	if (selectedSegment >= bezierCubics.size()) {
		selectedSegment = bezierCubics.size() - 1;
	}
	else if (selectedSegment < 0) {
		selectedSegment = 0;
	}

	float localT = segment - selectedSegment;

	return bezierCubics[selectedSegment].getPoint(localT);
}

int BezierCurve::getCubicsCount()
{
	return bezierCubics.size();
}

int BezierCurve::getControlPointCount()
{
	return controlPoints.size();
}

