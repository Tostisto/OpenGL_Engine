#pragma once

#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Rotation : public Transformation
{
private:
    float angle;
    glm::vec3 axis;

public:
    Rotation(float angle, glm::vec3 axis);

    glm::mat4 getMatrix() override;
};