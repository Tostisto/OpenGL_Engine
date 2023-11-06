#include "RotationAroundModel.h"

RotationAroundModel::RotationAroundModel(float angle, float distance, glm::vec3 axis, glm::mat4 modelMatrix, Drawable* centerModel)
{
	this->angle = angle;
	this->distance = distance;
    this->axis = axis;
	this->modelMatrix = modelMatrix;
	this->centerModel = centerModel;
}

glm::mat4 RotationAroundModel::getMatrix()
{
    glm::mat4 centerModelMatrix = centerModel->GetModelMatrix();
    glm::vec3 centerModelPos = glm::vec3(centerModelMatrix[3]);

    glm::vec3 modelPos = glm::vec3(modelMatrix[3]);

    glm::vec3 distance = glm::vec3(modelPos) - centerModelPos;

    fprintf(stderr, "Center: %f %f %f\n", centerModelPos.x, centerModelPos.y, centerModelPos.z);

    glm::mat4 translateToCenterMatrix = glm::translate(glm::mat4(1.0f), -distance);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
    glm::mat4 translateBackMatrix = glm::translate(glm::mat4(1.0f), distance);


    glm::mat4 resultMatrix = glm::mat4(1.0f);

    glm::mat4 inverse = glm::inverse(centerModelMatrix);

    resultMatrix *= inverse;

    resultMatrix = translateToCenterMatrix * rotationMatrix * translateBackMatrix;
    //resultMatrix = translateToCenterMatrix * rotationMatrix * translateBackMatrix;

    return resultMatrix;
}
