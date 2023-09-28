#include "Model.h"

Model::Model(float* points, int numPoints)
{
	this->points = points;

	// Create a vertex array object
	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * numPoints, this->points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

Model::~Model()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void Model::Draw()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}