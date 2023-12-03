#include "TransformCollection.h"

TransformCollection::TransformCollection()
{
	matrix = glm::mat4(1.0f);
	transformations = std::vector<Transformation*>();
}

void TransformCollection::addTransformation(Transformation* transform)
{
	transformations.push_back(transform);
}

void TransformCollection::addTransformationCollection(TransformCollection* transform_collection)
{
	for (auto& transform : transform_collection->transformations)
	{
		transformations.push_back(transform);
	}
}

glm::mat4 TransformCollection::getModelMatrix()
{
	matrix = glm::mat4(1.0f);
	for (auto& transform : transformations)
	{
		transform->transform(&matrix);
	}

	return matrix;
}