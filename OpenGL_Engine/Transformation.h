#pragma once

#include <glm/glm.hpp>

class Transformation
{
public:
    virtual glm::mat4 getMatrix() = 0;
    virtual ~Transformation() {}
};