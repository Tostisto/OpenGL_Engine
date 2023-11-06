#pragma once

#include <glm/glm.hpp>

class Transformation
{
public:
    virtual void transform(glm::mat4* matrix) = 0;
};