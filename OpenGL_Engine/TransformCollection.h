#pragma once

#include "Transformation.h"
#include <vector>

class TransformCollection
{
private:
    glm::mat4 matrix;
    std::vector<Transformation*> transformations;

public:
    TransformCollection();

    void addTransformation(Transformation* transform);
    void addTransformationCollection(TransformCollection* transform_collection);

    glm::mat4 getModelMatrix();
};