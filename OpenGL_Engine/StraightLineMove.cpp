#include "StraightLineMove.h"

StraightLineMove::StraightLineMove(const glm::vec3& start, const glm::vec3& end)
{
	this->start = start;
	this->direction = end - start;
    this->t = 0.0f;
    this->delta = 0.005f;
}

void StraightLineMove::transform(glm::mat4* matrix)
{
    glm::vec3 currentPosition = start + t * direction;
    *matrix = glm::translate(glm::mat4(1.0f), currentPosition);

    t += delta;
    if (t >= 1.0f || t <= 0.0f) {
        delta *= -1;
    }
}