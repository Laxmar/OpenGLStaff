#pragma once
#include <GL/glew.h>
#include <glm/detail/type_vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Color.h"

class Triangle
{
public:
	Triangle(GLfloat vertices[], Color& color = Color::black());
	~Triangle();
	void draw();
	void setColor(Color& color);
	Color& getColor();
	glm::vec3 GetCenterOfMass() const;

	glm::mat4 ModelMatrix;

private:
	const static int _verticesLenght = 9;
	GLuint _vertexBuffer;
	GLuint _vertexObjectArray;
	GLfloat _vertecies[_verticesLenght];
	glm::vec3 _centreOfMass;
	Color _color;

	glm::vec3 calculateCenterOfMass() const;
};

