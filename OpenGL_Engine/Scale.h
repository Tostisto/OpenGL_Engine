#pragma once

#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Scale : public Transformation
{
private:
    glm::vec3 scale;

public:
    Scale(glm::vec3 scale);

    glm::mat4 getMatrix() const override;
};

