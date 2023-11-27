#include "BezierMove.h"

BezierMove::BezierMove(float t, const glm::mat4x3& control_points) {
    M = glm::mat4(
        glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
        glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
        glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)
    );
    this->control_points = control_points;
    this->t = t;
    this->delta = 0.005f;
}

void BezierMove::transform(glm::mat4* matrix) {
    glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
    glm::vec3 p = parameters * M * glm::transpose(control_points);
    *matrix = glm::translate(*matrix, p);

    if (t >= 1.0f || t <= 0.0f) {
        delta *= -1;
    }
    t += delta;
}

