#pragma once

#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "BezierCurve.h"
#include "BezierCubic.h"


class BezierMove : public Transformation
{
private:
    BezierCurve* curve;
    float t = 0.0f;
    float speed = 0.001f;

public:
    BezierMove(BezierCurve* curve);
    void transform(glm::mat4* matrix) override;
};

