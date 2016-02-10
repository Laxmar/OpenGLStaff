#include "Triangle.h"



Triangle::Triangle(GLfloat vertices[])
{
	for (int i = 0; i < _verticesLenght; i++)
	{
		_vertecies[i] = vertices[i];
	}
	_centreOfMass = calculateCenterOfMass();

	glGenVertexArrays(1, &_vertexObjectArray);
	glBindVertexArray(_vertexObjectArray);

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertecies), _vertecies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDisableVertexAttribArray(0);
}

void Triangle::Draw()
{
	glBindVertexArray(_vertexObjectArray);

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}

glm::vec3  Triangle::GetCenterOfMass() const
{
	return _centreOfMass;
}

glm::vec3 Triangle::calculateCenterOfMass() const
{
	glm::vec3 centerOfMass;
	for (int i = 0; i < 3; i++)
	{
		centerOfMass.x += _vertecies[i * 3] / 3;
		centerOfMass.y += _vertecies[(i * 3 + 1)] / 3;
		centerOfMass.y += _vertecies[i * 3 + 2] / 3;
	}
	return centerOfMass;
}

Triangle::~Triangle()
{
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteVertexArrays(1, &_vertexObjectArray);
}
