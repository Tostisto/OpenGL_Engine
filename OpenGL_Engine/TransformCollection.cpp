#include "TransformCollection.h"

void TransformCollection::addTransformation(Transformation* transform)
{
    transformations.push_back(transform);
}

glm::mat4 TransformCollection::getMatrix() const
{
    glm::mat4 result(1.0f);

    for (int i = 0; i < transformations.size(); ++i) {
		result *= transformations[i]->getMatrix();
	}

    return result;
}