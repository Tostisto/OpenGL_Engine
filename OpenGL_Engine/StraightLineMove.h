#pragma once

#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

class StraightLineMove : public Transformation
{
private:
private:
    glm::vec3 start;
    glm::vec3 direction;
    float t;
    float delta;

public:
    StraightLineMove(const glm::vec3& start, const glm::vec3& end);
    void transform(glm::mat4* matrix) override;
};

