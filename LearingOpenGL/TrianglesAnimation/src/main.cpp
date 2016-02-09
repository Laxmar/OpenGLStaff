#include <stdio.h>
#include <iostream>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "glm/gtx/rotate_vector.hpp"
#include <glut.h>

#include "shader.h"
#include "Triangle.h"
#include <memory>

using namespace std;
void initVertexArray();
void createTriangle();
void renderScence();
void keyboardCallback(unsigned char key, int x, int y);
void idle();

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int Axis = Xaxis;
GLfloat Theta[NumAxes] = { 0.0, 0.0, 0.0 };
GLuint theta; // The location of the "theta" shader uniform variable

unique_ptr<Triangle> firstTriangle;
unique_ptr<Triangle> secondTriangle;


int main(int argc, char *argv[])
{
	int window;
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);		
	window = glutCreateWindow("Triangles Animation");	
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
	GLuint programID = LoadShaders("rotationVerShader.vert", "simpleFragmentShader.frag");
	glUseProgram(programID);
	theta = glGetUniformLocation(programID, "theta");

	glutDisplayFunc(renderScence);		
	glutKeyboardFunc(keyboardCallback);		
	glutIdleFunc(idle);

	createTriangle();

	glutMainLoop();			

	return 0;
}

void renderScence()
{
	glClear((GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	firstTriangle->Draw();
	secondTriangle->Draw();
	glUniform3fv(theta, 1, Theta);
	glutSwapBuffers();
}

void idle()
{
	for (int Axis = 0; Axis < 2; Axis++)
	{
		Theta[Axis] += 0.01f;
		if (Theta[Axis] > 360.0) {
			Theta[Axis] -= 360.0;
		}
	}

	glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y)
{
	const int escCode = 27;
	if (key == 'q' || (int)key == escCode)
		exit(EXIT_SUCCESS);
}

void createTriangle() {

	 GLfloat firstTriangleVertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f,
	};


	firstTriangle = std::make_unique<Triangle>(firstTriangleVertices);
	GLfloat secondTriangleVertices[] = {
		-1.0f, -1.0f, 0.0f,
		-0.5f, -1.0f, 0.0f,
		-1.0f, -0.5f, 0.0f,
	};
	secondTriangle = std::make_unique<Triangle>(secondTriangleVertices);
	printf("cetner of mass 1tri %f %f %f \n", firstTriangle->GetCenterOfMass().x, firstTriangle->GetCenterOfMass().y, firstTriangle->GetCenterOfMass().z);
	printf("cetner of mass 2tri %f %f %f \n", secondTriangle->GetCenterOfMass().x, secondTriangle->GetCenterOfMass().y, secondTriangle->GetCenterOfMass().z);
}
