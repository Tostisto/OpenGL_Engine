#include "BezierMove.h"

BezierMove::BezierMove(BezierCurve* curve)
{
    this->curve = curve;

}

void BezierMove::transform(glm::mat4* matrix) {

    t += speed;
    
    if (t > 1.0f) {
		t = 0.0f;
	}


    glm::vec3 position = curve->getPoint(t);
	*matrix = glm::translate(*matrix, position);
}