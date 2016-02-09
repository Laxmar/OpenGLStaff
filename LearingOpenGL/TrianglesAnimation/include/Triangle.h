#pragma once
#include <GL/glew.h>

class Triangle
{
public:
	Triangle(GLfloat vertices[]);
	~Triangle();
	void Draw();

private:
	const static int _verticesLenght = 9;
	GLuint _vertexBuffer;
	GLuint _vertexObjectArray;
	GLfloat _vertecies[_verticesLenght];
};

