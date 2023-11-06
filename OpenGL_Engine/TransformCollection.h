#pragma once

#include "Transformation.h"
#include <vector>

class TransformCollection : public Transformation
{
private:
    glm::mat4 matrix = glm::mat4(1.0f);
    std::vector<Transformation*> transformations;

public:
    TransformCollection();

    void addTransformation(Transformation* transform);
    void addTransformationCollection(TransformCollection* transform_collection);
    void transform(glm::mat4* matrix) override;

    glm::mat4 transform();
};