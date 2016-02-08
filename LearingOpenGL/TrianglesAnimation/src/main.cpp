#include <stdio.h>
#include <iostream>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glut.h>

#include "shader.h"

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


int main(int argc, char *argv[])
{
	int window;
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);		
	window = glutCreateWindow("Triangles Animation");	

	glewInit();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0.7, 0.7, 1);
	GLuint programID = LoadShaders("shaders/rotationVerShader.vert", "shaders/simpleFragmentShader.frag");//"shaders/simpleVertexShader.vert"
	glUseProgram(programID);
	theta = glGetUniformLocation(programID, "theta");


	glutDisplayFunc(renderScence);		
	glutKeyboardFunc(keyboardCallback);		
	glutIdleFunc(idle);

	initVertexArray();
	createTriangle();

	glutMainLoop();			

	return 0;
}

void renderScence()
{
	glEnableVertexAttribArray(0);
	glClear((GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	glUniform3fv(theta, 1, Theta);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);


	glutSwapBuffers();
}

void idle()
{
	Axis = 1;
	Theta[Axis] += 0.01;
	Axis = 2;
	Theta[Axis] += 0.01;
	
	if (Theta[Axis] > 360.0) {
		Theta[Axis] -= 360.0;
	}
	glutPostRedisplay(); // TODO check
}

void keyboardCallback(unsigned char key, int x, int y)
{
	const int escCode = 27;
	if (key == 'q' || (int)key == escCode)
		exit(EXIT_SUCCESS);
}

void initVertexArray() {
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void createTriangle() {

	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f,
	};
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT,  GL_FALSE, 0,(void*)0);
	glDisableVertexAttribArray(0);
}