#pragma once

#include "Transformation.h"
#include <vector>

class TransformCollection
{
private:
    glm::mat4 matrix = glm::mat4(1.0f);
    std::vector<Transformation*> transformations;

public:
    TransformCollection();

    void addTransformation(Transformation* transform);
    void addTransformationCollection(TransformCollection* transform_collection);

    glm::mat4 transform();
};