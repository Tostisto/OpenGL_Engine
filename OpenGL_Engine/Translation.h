#pragma once

#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Translation : public Transformation
{
private:
    glm::vec3 translation;

public:
    Translation(glm::vec3 translation);

    glm::mat4 getMatrix() override;
};