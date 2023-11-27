#pragma once

#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class BezierMove : public Transformation
{
private:
    glm::mat4 M;
    float t;
    float delta;
    glm::mat4x3 control_points;

public:
    BezierMove(float t, const glm::mat4x3& control_points);
    void transform(glm::mat4* matrix) override;
};

