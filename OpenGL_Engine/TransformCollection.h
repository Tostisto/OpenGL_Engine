#pragma once

#include "Transformation.h"
#include <vector>

class TransformCollection : public Transformation
{
private:
    std::vector<Transformation*> transformations;

public:
    void addTransformation(Transformation* transform);
    glm::mat4 getMatrix() const override;
};

